/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/smartdashboard/Sendable.h>
#include <frc/smartdashboard/SendableHelper.h>

#include <string>

#include "Subsystem.h"

namespace frc2 {
/**
 * A base for subsystems that handles registration in the constructor, and
 * provides a more intuitive method for setting the default command.
 */
class SubsystemBase : public Subsystem,
                      public frc::Sendable,
                      public frc::SendableHelper<SubsystemBase> {
 public:
  void InitSendable(frc::SendableBuilder& builder) override;

  /**
   * Gets the name of this Subsystem.
   *
   * @return Name
   */
  std::string GetName() const;

  /**
   * Sets the name of this Subsystem.
   *
   * @param name name
   */
  void SetName(const wpi::Twine& name);

  /**
   * Gets the subsystem name of this Subsystem.
   *
   * @return Subsystem name
   */
  std::string GetSubsystem() const;

  /**
   * Sets the subsystem name of this Subsystem.
   *
   * @param subsystem subsystem name
   */
  void SetSubsystem(const wpi::Twine& name);

  /**
   * Associate a Sendable with this Subsystem.
   * Also update the child's name.
   *
   * @param name name to give child
   * @param child sendable
   */
  void AddChild(std::string name, frc::Sendable* child);

 protected:
  SubsystemBase();
};
}  // namespace frc2
