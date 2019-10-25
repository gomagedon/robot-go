/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <units/units.h>
#include <wpi/Twine.h>

#include "CommandBase.h"
#include "CommandHelper.h"
#include "frc/Timer.h"

namespace frc2 {
/**
 * A command that does nothing but takes a specified amount of time to finish.
 * Useful for CommandGroups.  Can also be subclassed to make a command with an
 * internal timer.
 */
class WaitCommand : public CommandHelper<CommandBase, WaitCommand> {
 public:
  /**
   * Creates a new WaitCommand.  This command will do nothing, and end after the
   * specified duration.
   *
   * @param duration the time to wait
   */
  explicit WaitCommand(units::second_t duration);

  WaitCommand(WaitCommand&& other) = default;

  WaitCommand(const WaitCommand& other) = default;

  void Initialize() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  bool RunsWhenDisabled() const override;

 protected:
  frc::Timer m_timer;

 private:
  units::second_t m_duration;
};
}  // namespace frc2
