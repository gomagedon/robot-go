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
#include <utility>

#include "CommandBase.h"
#include "CommandGroupBase.h"
#include "CommandHelper.h"

namespace frc2 {
/**
 * A command that runs another command in perpetuity, ignoring that command's
 * end conditions.  While this class does not extend {@link CommandGroupBase},
 * it is still considered a CommandGroup, as it allows one to compose another
 * command within it; the command instances that are passed to it cannot be
 * added to any other groups, or scheduled individually.
 *
 * <p>As a rule, CommandGroups require the union of the requirements of their
 * component commands.
 */
class PerpetualCommand : public CommandHelper<CommandBase, PerpetualCommand> {
 public:
  /**
   * Creates a new PerpetualCommand.  Will run another command in perpetuity,
   * ignoring that command's end conditions, unless this command itself is
   * interrupted.
   *
   * @param command the command to run perpetually
   */
  explicit PerpetualCommand(std::unique_ptr<Command>&& command);

  /**
   * Creates a new PerpetualCommand.  Will run another command in perpetuity,
   * ignoring that command's end conditions, unless this command itself is
   * interrupted.
   *
   * @param command the command to run perpetually
   */
  template <class T, typename = std::enable_if_t<std::is_base_of_v<
                         Command, std::remove_reference_t<T>>>>
  explicit PerpetualCommand(T&& command)
      : PerpetualCommand(std::make_unique<std::remove_reference_t<T>>(
            std::forward<T>(command))) {}

  PerpetualCommand(PerpetualCommand&& other) = default;

  // No copy constructors for command groups
  PerpetualCommand(const PerpetualCommand& other) = delete;

  // Prevent template expansion from emulating copy ctor
  PerpetualCommand(PerpetualCommand&) = delete;

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

 private:
  std::unique_ptr<Command> m_command;
};
}  // namespace frc2

#ifdef _WIN32
#pragma warning(pop)
#endif
