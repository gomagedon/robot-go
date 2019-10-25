/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/ErrorBase.h>

#include <memory>
#include <set>
#include <vector>

#include "CommandBase.h"

namespace frc2 {

/**
 * A base for CommandGroups.  Statically tracks commands that have been
 * allocated to groups to ensure those commands are not also used independently,
 * which can result in inconsistent command state and unpredictable execution.
 */
class CommandGroupBase : public CommandBase {
 public:
  /**
   * Requires that the specified command not have been already allocated to a
   * CommandGroup. Reports an error if the command is already grouped.
   *
   * @param commands The command to check
   * @return True if all the command is ungrouped.
   */
  static bool RequireUngrouped(Command& command);

  /**
   * Requires that the specified commands not have been already allocated to a
   * CommandGroup. Reports an error if any of the commands are already grouped.
   *
   * @param commands The commands to check
   * @return True if all the commands are ungrouped.
   */
  static bool RequireUngrouped(wpi::ArrayRef<std::unique_ptr<Command>>);

  /**
   * Requires that the specified commands not have been already allocated to a
   * CommandGroup. Reports an error if any of the commands are already grouped.
   *
   * @param commands The commands to check
   * @return True if all the commands are ungrouped.
   */
  static bool RequireUngrouped(std::initializer_list<Command*>);

  /**
   * Adds the given commands to the command group.
   *
   * @param commands The commands to add.
   */
  virtual void AddCommands(
      std::vector<std::unique_ptr<Command>>&& commands) = 0;
};
}  // namespace frc2
