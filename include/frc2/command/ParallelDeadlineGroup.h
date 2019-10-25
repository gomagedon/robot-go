/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable : 4521)
#endif

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "CommandGroupBase.h"
#include "CommandHelper.h"

namespace frc2 {
/**
 * A CommandGroup that runs a set of commands in parallel, ending only when a
 * specific command (the "deadline") ends, interrupting all other commands that
 * are still running at that point.
 *
 * <p>As a rule, CommandGroups require the union of the requirements of their
 * component commands.
 */
class ParallelDeadlineGroup
    : public CommandHelper<CommandGroupBase, ParallelDeadlineGroup> {
 public:
  /**
   * Creates a new ParallelDeadlineGroup.  The given commands (including the
   * deadline) will be executed simultaneously.  The CommandGroup will finish
   * when the deadline finishes, interrupting all other still-running commands.
   * If the CommandGroup is interrupted, only the commands still running will be
   * interrupted.
   *
   * @param deadline the command that determines when the group ends
   * @param commands the commands to be executed
   */
  ParallelDeadlineGroup(std::unique_ptr<Command>&& deadline,
                        std::vector<std::unique_ptr<Command>>&& commands);
  /**
   * Creates a new ParallelDeadlineGroup.  The given commands (including the
   * deadline) will be executed simultaneously.  The CommandGroup will finish
   * when the deadline finishes, interrupting all other still-running commands.
   * If the CommandGroup is interrupted, only the commands still running will be
   * interrupted.
   *
   * @param deadline the command that determines when the group ends
   * @param commands the commands to be executed
   */
  template <class T, class... Types,
            typename = std::enable_if_t<
                std::is_base_of_v<Command, std::remove_reference_t<T>>>,
            typename = std::enable_if_t<std::conjunction_v<
                std::is_base_of<Command, std::remove_reference_t<Types>>...>>>
  explicit ParallelDeadlineGroup(T&& deadline, Types&&... commands) {
    SetDeadline(std::make_unique<std::remove_reference_t<T>>(
        std::forward<T>(deadline)));
    AddCommands(std::forward<Types>(commands)...);
  }

  ParallelDeadlineGroup(ParallelDeadlineGroup&& other) = default;

  // No copy constructors for command groups
  ParallelDeadlineGroup(const ParallelDeadlineGroup&) = delete;

  // Prevent template expansion from emulating copy ctor
  ParallelDeadlineGroup(ParallelDeadlineGroup&) = delete;

  template <class... Types,
            typename = std::enable_if_t<std::conjunction_v<
                std::is_base_of<Command, std::remove_reference_t<Types>>...>>>
  void AddCommands(Types&&... commands) {
    std::vector<std::unique_ptr<Command>> foo;
    ((void)foo.emplace_back(std::make_unique<std::remove_reference_t<Types>>(
         std::forward<Types>(commands))),
     ...);
    AddCommands(std::move(foo));
  }

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  bool RunsWhenDisabled() const override;

 private:
  void AddCommands(std::vector<std::unique_ptr<Command>>&& commands) override;

  void SetDeadline(std::unique_ptr<Command>&& deadline);

  std::unordered_map<std::unique_ptr<Command>, bool> m_commands;
  Command* m_deadline;
  bool m_runWhenDisabled{true};
  bool isRunning = false;
};
}  // namespace frc2

#ifdef _WIN32
#pragma warning(pop)
#endif
