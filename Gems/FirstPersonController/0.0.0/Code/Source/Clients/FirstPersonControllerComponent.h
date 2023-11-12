/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once
#include <FirstPersonController/FirstPersonControllerComponentBus.h>

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <AzCore/Math/Vector3.h>
#include <AzCore/Math/Quaternion.h>
#include <AzCore/std/containers/map.h>

#include <AzFramework/Physics/Common/PhysicsSceneQueries.h>
#include <AzFramework/Physics/CharacterBus.h>
#include <AzFramework/Input/Events/InputChannelEventListener.h>

#include <StartingPointInput/InputEventNotificationBus.h>

#include <PhysXCharacters/API/CharacterController.h>

namespace FirstPersonController
{
    class FirstPersonControllerComponent
        : public AZ::Component
        , public AZ::TickBus::Handler
        , protected Physics::CharacterNotificationBus::Handler
        , public AzFramework::InputChannelEventListener
        , public StartingPointInput::InputEventNotificationBus::MultiHandler
        , public FirstPersonControllerComponentRequestBus::Handler
    {
    public:
        AZ_COMPONENT(FirstPersonControllerComponent, "{0a47c7c2-0f94-48dd-8e3f-fd55c30475b9}");

        static void Reflect(AZ::ReflectContext* rc);

        // AZ::Component interface implementation
        void Activate() override;
        void Deactivate() override;

        // Physics::CharacterNotificationBus override
        void OnCharacterActivated(const AZ::EntityId& entityId) override;

        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);

        // AZ::InputEventNotificationBus interface
        void OnPressed(float value) override;
        void OnReleased(float value) override;
        void OnHeld(float value) override;

        // AzFramework::InputChannelEventListener
        bool OnInputChannelEventFiltered(const AzFramework::InputChannel& inputChannel) override;

        // Gamepad Events
        void OnGamepadEvent(const AzFramework::InputChannel& inputChannel);

        // TickBus interface
        void OnTick(float deltaTime, AZ::ScriptTimePoint) override;

        // FirstPersonControllerRequestBus
        AZ::Entity* GetActiveCameraEntityPtr() const override;
        AZ::EntityId GetActiveCameraEntityId() const override;
        void ReacquireChildEntityIds() override;
        void ReacquireCapsuleDimensions() override;
        void ReacquireMaxSlopeAngle() override;
        AZStd::string GetForwardEventName() const override;
        void SetForwardEventName(const AZStd::string& new_strForward) override;
        float GetForwardScale() const override;
        void SetForwardScale(const float& new_forwardScale) override;
        float GetForwardInputValue() const override;
        void SetForwardInputValue(const float& new_forwardValue) override;
        AZStd::string GetBackEventName() const override;
        void SetBackEventName(const AZStd::string& new_strBack) override;
        float GetBackScale() const override;
        void SetBackScale(const float& new_backScale) override;
        float GetBackInputValue() const override;
        void SetBackInputValue(const float& new_backValue) override;
        AZStd::string GetLeftEventName() const override;
        void SetLeftEventName(const AZStd::string& new_strLeft) override;
        float GetLeftScale() const override;
        void SetLeftScale(const float& new_leftScale) override;
        float GetLeftInputValue() const override;
        void SetLeftInputValue(const float& new_leftValue) override;
        AZStd::string GetRightEventName() const override;
        void SetRightEventName(const AZStd::string& new_strRight) override;
        float GetRightScale() const override;
        void SetRightScale(const float& new_rightScale) override;
        float GetRightInputValue() const override;
        void SetRightInputValue(const float& new_rightValue) override;
        AZStd::string GetYawEventName() const override;
        void SetYawEventName(const AZStd::string& new_strYaw) override;
        float GetYawInputValue() const override;
        void SetYawInputValue(const float& new_yawValue) override;
        AZStd::string GetPitchEventName() const override;
        void SetPitchEventName(const AZStd::string& new_strPitch) override;
        float GetPitchInputValue() const override;
        void SetPitchInputValue(const float& new_pitchValue) override;
        AZStd::string GetSprintEventName() const override;
        void SetSprintEventName(const AZStd::string& new_strSprint) override;
        float GetSprintInputValue() const override;
        void SetSprintInputValue(const float& new_sprintValue) override;
        AZStd::string GetCrouchEventName() const override;
        void SetCrouchEventName(const AZStd::string& new_strCrouch) override;
        float GetCrouchInputValue() const override;
        void SetCrouchInputValue(const float& new_crouchValue) override;
        AZStd::string GetJumpEventName() const override;
        void SetJumpEventName(const AZStd::string& new_strJump) override;
        float GetJumpInputValue() const override;
        void SetJumpInputValue(const float& new_jumpValue) override;
        bool GetGrounded() const override;
        void SetGroundedForTick(const bool& new_grounded) override;
        AZStd::vector<AzPhysics::SceneQueryHit> GetGroundSceneQueryHits() const override;
        AZStd::vector<AzPhysics::SceneQueryHit> GetGroundCloseSceneQueryHits() const override;
        AZ::Vector3 GetGroundSumNormalsDirection() const override;
        AZ::Vector3 GetGroundCloseSumNormalsDirection() const override;
        AzPhysics::SceneQuery::ResultFlags GetSceneQueryHitResultFlags(AzPhysics::SceneQueryHit hit) const override;
        AZ::EntityId GetSceneQueryHitEntityId(AzPhysics::SceneQueryHit hit) const override;
        AZ::Vector3 GetSceneQueryHitNormal(AzPhysics::SceneQueryHit hit) const override;
        AZ::Vector3 GetSceneQueryHitPosition(AzPhysics::SceneQueryHit hit) const override;
        float GetSceneQueryHitDistance(AzPhysics::SceneQueryHit hit) const override;
        Physics::MaterialId GetSceneQueryHitMaterialId(AzPhysics::SceneQueryHit hit) const override;
        Physics::Shape* GetSceneQueryHitShapePtr(AzPhysics::SceneQueryHit hit) const override;
        AzPhysics::SimulatedBodyHandle GetSceneQueryHitSimulatedBodyHandle(AzPhysics::SceneQueryHit hit) const override;
        bool GetGroundClose() const override;
        void SetGroundCloseForTick(const bool& new_groundClose) override;
        AZStd::string GetGroundedCollisionGroupName() const override;
        void SetGroundedCollisionGroup(const AZStd::string& new_groundedCollisionGroup) override;
        float GetAirTime() const override;
        float GetGravity() const override;
        void SetGravity(const float& new_gravity) override;
        AZ::Vector3 GetPrevTargetVelocityWorld() const override;
        AZ::Vector3 GetPrevTargetVelocityHeading() const override;
        float GetVelocityCloseTolerance() const override;
        void SetVelocityCloseTolerance(const float& new_velocityCloseTolerance) override;
        AZ::Vector3 TiltVectorXCrossY(const AZ::Vector2 vXY, const AZ::Vector3& newXCrossYDirection) override;
        AZ::Vector3 GetVelocityXCrossYDirection() const override;
        void SetVelocityXCrossYDirection(const AZ::Vector3& new_velocityXCrossYDirection) override;
        bool GetVelocityXCrossYTracksNormal() const override;
        void SetVelocityXCrossYTracksNormal(const bool& new_velocityXCrossYTracksNormal) override;
        AZ::Vector3 GetVelocityZPosDirection() const override;
        void SetVelocityZPosDirection(const AZ::Vector3& new_velocityZPosDirection) override;
        AZ::Vector3 GetSphereCastsAxisDirectionPose() const override;
        void SetSphereCastsAxisDirectionPose(const AZ::Vector3& new_sphereCastsAxisDirectionPose) override;
        AZ::Vector3 GetVectorAnglesBetweenVectorsRadians(const AZ::Vector3& v1, const AZ::Vector3& v2) override;
        AZ::Vector3 GetVectorAnglesBetweenVectorsDegrees(const AZ::Vector3& v1, const AZ::Vector3& v2) override;
        AZ::Vector2 CreateEllipseScaledVector(const AZ::Vector2& unscaledVector, float forwardScale, float backScale, float leftScale, float rightScale) override;
        float GetJumpHeldGravityFactor() const override;
        void SetJumpHeldGravityFactor(const float& new_jumpHeldGravityFactor) override;
        float GetJumpFallingGravityFactor() const override;
        void SetJumpFallingGravityFactor(const float& new_jumpFallingGravityFactor) override;
        float GetJumpAccelFactor() const override;
        void SetJumpAccelFactor(const float& new_jumpAccelFactor) override;
        bool GetUpdateXYAscending() const override;
        void SetUpdateXYAscending(const bool& new_updateXYAscending) override;
        bool GetUpdateXYDescending() const override;
        void SetUpdateXYDescending(const bool& new_updateXYDecending) override;
        bool GetUpdateXYOnlyNearGround() const override;
        void SetUpdateXYOnlyNearGround(const bool& new_updateXYOnlyNearGround) override;
        bool GetAddVelocityForTimestepVsTick() const override;
        void SetAddVelocityForTimestepVsTick(const bool& new_addVelocityForTimestepVsTick) override;
        float GetPhysicsTimestepScaleFactor() const override;
        void SetPhysicsTimestepScaleFactor(const float& new_physicsTimestepScaleFactor) override;
        bool GetScriptSetsTargetVelocityXY() const override;
        void SetScriptSetsTargetVelocityXY(const bool& new_scriptSetsTargetVelocityXY) override;
        AZ::Vector2 GetTargetVelocityXY() const override;
        void SetTargetVelocityXY(const AZ::Vector2& new_scriptTargetVelocityXY) override;
        AZ::Vector2 GetCorrectedVelocityXY() const override;
        void SetCorrectedVelocityXY(const AZ::Vector2& new_correctedVelocityXY) override;
        float GetCorrectedVelocityZ() const override;
        void SetCorrectedVelocityZ(const float& new_correctedVelocityZ) override;
        AZ::Vector2 GetApplyVelocityXY() const override;
        void SetApplyVelocityXY(const AZ::Vector2& new_applyVelocityXY) override;
        AZ::Vector3 GetAddVelocityWorld() const override;
        void SetAddVelocityWorld(const AZ::Vector3& new_addVelocityWorld) override;
        AZ::Vector3 GetAddVelocityHeading() const override;
        void SetAddVelocityHeading(const AZ::Vector3& new_addVelocityHeading) override;
        float GetApplyVelocityZ() const override;
        void SetApplyVelocityZ(const float& new_applyVelocityZ) override;
        float GetJumpInitialVelocity() const override;
        void SetJumpInitialVelocity(const float& new_jumpInitialVelocity) override;
        float GetJumpSecondInitialVelocity() const override;
        void SetJumpSecondInitialVelocity(const float& new_jumpInitialVelocity) override;
        bool GetJumpReqRepress() const override;
        void SetJumpReqRepress(const bool& new_jumpReqRepress) override;
        bool GetJumpHeld() const override;
        void SetJumpHeld(const bool& new_jumpHeld) override;
        bool GetDoubleJump() const override;
        void SetDoubleJump(const bool& new_doubleJumpEnabled) override;
        float GetGroundedOffset() const override;
        void SetGroundedOffset(const float& new_groundedSphereCastOffset) override;
        float GetGroundCloseOffset() const override;
        void SetGroundCloseOffset(const float& new_groundCloseSphereCastOffset) override;
        float GetJumpHoldDistance() const override;
        void SetJumpHoldDistance(const float& new_jumpHoldDistance) override;
        float GetJumpHeadSphereCastOffset() const override;
        void SetJumpHeadSphereCastOffset(const float& new_jumpHeadSphereCastOffset) override;
        bool GetHeadHitSetsApogee() const override;
        void SetHeadHitSetsApogee(const bool& new_headHitSetsApogee) override;
        bool GetHeadHit() const override;
        void SetHeadHit(const bool& new_headHit) override;
        bool GetJumpHeadIgnoreDynamicRigidBodies() const override;
        void SetJumpHeadIgnoreDynamicRigidBodies(const bool& new_jumpHeadIgnoreDynamicRigidBodies) override;
        AZStd::string GetHeadCollisionGroupName() const override;
        void SetHeadCollisionGroupByName(const AZStd::string& new_headCollisionGroupName) override;
        AZStd::vector<AZ::EntityId> GetHeadHitEntityIds() const override;
        bool GetStandPrevented() const override;
        void SetStandPrevented(const bool& new_standPrevented) override;
        bool GetStandIgnoreDynamicRigidBodies() const override;
        void SetStandIgnoreDynamicRigidBodies(const bool& new_standIgnoreDynamicRigidBodies) override;
        AZStd::string GetStandCollisionGroupName() const override;
        void SetStandCollisionGroupByName(const AZStd::string& new_standCollisionGroupName) override;
        AZStd::vector<AZ::EntityId> GetStandPreventedEntityIds() const override;
        float GetGroundSphereCastsRadiusPercentageIncrease() const override;
        void SetGroundSphereCastsRadiusPercentageIncrease(const float& new_groundSphereCastsRadiusPercentageIncrease) override;
        float GetMaxGroundedAngleDegrees() const override;
        void SetMaxGroundedAngleDegrees(const float& new_maxGroundedAngleDegrees) override;
        float GetTopWalkSpeed() const override;
        void SetTopWalkSpeed(const float& new_speed) override;
        float GetWalkAcceleration() const override;
        void SetWalkAcceleration(const float& new_accel) override;
        float GetTotalLerpTime() const override;
        void SetTotalLerpTime(const float& new_totalLerpTime) override;
        float GetLerpTime() const override;
        void SetLerpTime(const float& new_lerpTime) override;
        float GetDecelerationFactor() const override;
        void SetDecelerationFactor(const float& new_decel) override;
        float GetOpposingDecel() const override;
        void SetOpposingDecel(const float& new_opposingDecel) override;
        bool GetAccelerating() const override;
        bool GetDecelerationFactorApplied() const override;
        bool GetOpposingDecelFactorApplied() const override;
        bool GetInstantVelocityRotation() const override;
        void SetInstantVelocityRotation(const bool& new_instantVelocityRotation) override;
        bool GetVelocityXYIgnoresObstacles() const override;
        void SetVelocityXYIgnoresObstacles(const bool& new_velocityXYIgnoresObstacles) override;
        bool GetGravityIgnoresObstacles() const override;
        void SetGravityIgnoresObstacles(const bool& new_gravityIgnoresObstacles) override;
        bool GetPosZIgnoresObstacles() const override;
        void SetPosZIgnoresObstacles(const bool& new_posZIgnoresObstacles) override;
        bool GetJumpAllowedWhenGravityPrevented() const override;
        void SetJumpAllowedWhenGravityPrevented(const bool& new_jumpAllowedWhenGravityPrevented) override;
        bool GetHitSomething() const override;
        void SetHitSomething(const bool& new_hitSomething) override;
        bool GetGravityPrevented() const override;
        void SetGravityPrevented(const bool& new_gravityPrevented) override;
        float GetSprintScaleForward() const override;
        void SetSprintScaleForward(const float& new_sprintScaleForward) override;
        float GetSprintScaleBack() const override;
        void SetSprintScaleBack(const float& new_sprintScaleBack) override;
        float GetSprintScaleLeft() const override;
        void SetSprintScaleLeft(const float& new_sprintScaleLeft) override;
        float GetSprintScaleRight() const override;
        void SetSprintScaleRight(const float& new_sprintScaleRight) override;
        float GetSprintAccelScale() const override;
        void SetSprintAccelScale(const float& new_sprintAccelScale) override;
        float GetSprintAccumulatedAccel() const override;
        void SetSprintAccumulatedAccel(const float& new_sprintAccumulatedAccel) override;
        float GetSprintMaxTime() const override;
        void SetSprintMaxTime(const float& new_sprintMaxTime) override;
        float GetSprintHeldTime() const override;
        void SetSprintHeldTime(const float& new_sprintHeldDuration) override;
        float GetSprintRegenRate() const override;
        void SetSprintRegenRate(const float& new_sprintRegenRate) override;
        float GetStaminaPercentage() const override;
        void SetStaminaPercentage(const float& new_staminaPercentage) override;
        bool GetStaminaIncreasing() const override;
        bool GetStaminaDecreasing() const override;
        bool GetSprintUsesStamina() const override;
        void SetSprintUsesStamina(const bool& new_sprintUsesStamina) override;
        bool GetRegenerateStaminaAutomatically() const override;
        void SetRegenerateStaminaAutomatically(const bool& new_regenerateStaminaAutomatically) override;
        bool GetSprinting() const override;
        float GetSprintCooldownTime() const override;
        void SetSprintCooldownTime(const float& new_sprintCooldownTime) override;
        float GetSprintCooldown() const override;
        void SetSprintCooldown(const float& new_sprintCooldown) override;
        float GetSprintPauseTime() const override;
        void SetSprintPauseTime(const float& new_sprintPauseTime) override;
        float GetSprintPause() const override;
        void SetSprintPause(const float& new_sprintPause) override;
        bool GetSprintBackwards() const override;
        void SetSprintBackwards(const bool& new_sprintBackwards) override;
        bool GetSprintWhileCrouched() const override;
        void SetSprintWhileCrouched(const bool& new_sprintWhileCrouched) override;
        bool GetCrouching() const override;
        void SetCrouching(const bool& new_crouching) override;
        bool GetCrouched() const override;
        bool GetStanding() const override;
        float GetCrouchedPercentage() const override;
        bool GetCrouchScriptLocked() const override;
        void SetCrouchScriptLocked(const bool& new_crouchScriptLocked) override;
        float GetCrouchScale() const override;
        void SetCrouchScale(const float& new_crouchScale) override;
        float GetCrouchDistance() const override;
        void SetCrouchDistance(const float& new_crouchDistance) override;
        float GetCrouchTime() const override;
        void SetCrouchTime(const float& new_crouchTime) override;
        float GetUncrouchHeadSphereCastOffset() const override;
        void SetUncrouchHeadSphereCastOffset(const float& new_uncrouchHeadSphereCastOffset) override;
        bool GetCrouchEnableToggle() const override;
        void SetCrouchEnableToggle(const bool& new_crouchEnableToggle) override;
        bool GetCrouchJumpCausesStanding() const override;
        void SetCrouchJumpCausesStanding(const bool& new_crouchJumpCausesStanding) override;
        bool GetCrouchSprintCausesStanding() const override;
        void SetCrouchSprintCausesStanding(const bool& new_crouchSprintCausesStanding) override;
        bool GetCrouchPriorityWhenSprintPressed() const override;
        void SetCrouchPriorityWhenSprintPressed(const bool& new_crouchPriorityWhenSprintPressed) override;
        bool GetSprintViaScript() const override;
        void SetSprintViaScript(const bool& new_sprintViaScript) override;
        bool GetSprintEnableDisableScript() const override;
        void SetSprintEnableDisableScript(const bool& new_sprintEnableDisableScript) override;
        float GetCameraYawSensitivity() const override;
        void SetCameraYawSensitivity(const float& new_yawSensitivity) override;
        float GetCameraPitchSensitivity() const override;
        void SetCameraPitchSensitivity(const float& new_pitchSensitivity) override;
        float GetCameraPitchMaxAngleRadians() const override;
        void SetCameraPitchMaxAngleRadians(const float& new_pitchMaxAngleRadians) override;
        float GetCameraPitchMaxAngleDegrees() const override;
        void SetCameraPitchMaxAngleDegrees(const float& new_pitchMaxAngleDegrees) override;
        float GetCameraPitchMinAngleRadians() const override;
        void SetCameraPitchMinAngleRadians(const float& new_pitchMinAngleRadians) override;
        float GetCameraPitchMinAngleDegrees() const override;
        void SetCameraPitchMinAngleDegrees(const float& new_pitchMinAngleDegrees) override;
        float GetCameraRotationDampFactor() const override;
        void SetCameraRotationDampFactor(const float& new_rotationDamp) override;
        bool GetCameraSlerpInsteadOfLerpRotation() const override;
        void SetCameraSlerpInsteadOfLerpRotation(const bool& new_cameraSlerpInsteadOfLerpRotation) override;
        bool GetUpdateCameraYawIgnoresInput() const override;
        void SetUpdateCameraYawIgnoresInput(const bool& new_updateCameraYawIgnoresInput) override;
        bool GetUpdateCameraPitchIgnoresInput() const override;
        void SetUpdateCameraPitchIgnoresInput(const bool& new_updateCameraPitchIgnoresInput) override;
        void UpdateCameraYaw(const float& new_cameraYawAngle) override;
        void UpdateCameraPitch(const float& new_cameraPitchAngle) override;
        float GetHeading() const override;
        void SetHeadingForTick(const float& new_currentHeading) override;
        float GetPitch() const override;

    private:
        // Input event assignment and notification bus connection
        void AssignConnectInputEvents();

        // Active camera entity pointer
        AZ::Entity* m_activeCameraEntity = nullptr;

        // Child EntityIds
        bool m_obtainedChildIds = false;
        AZStd::vector<AZ::EntityId> m_children;

        // Called on each tick
        void ProcessInput(const float& deltaTime, const bool& tickElseTimestep);

        // Various methods used to implement the First Person Controller functionality
        void CheckGrounded(const float& deltaTime);
        void UpdateVelocityXY(const float& deltaTime);
        void UpdateJumpMaxHoldTime();
        void UpdateVelocityZ(const float& deltaTime);
        void UpdateRotation(const float& deltaTime);
        AZ::Vector2 LerpVelocityXY(const AZ::Vector2& targetVelocity, const float& deltaTime);
        void SmoothRotation(const float& deltaTime);
        void SprintManager(const AZ::Vector2& targetVelocity, const float& deltaTime);
        void CrouchManager(const float& deltaTime);

        // FirstPersonControllerNotificationBus
        void OnGroundHit();
        void OnGroundSoonHit();
        void OnUngrounded();
        void OnStartedFalling();
        void OnStartedMoving();
        void OnTargetVelocityReached();
        void OnStopped();
        void OnTopWalkSpeedReached();
        void OnTopSprintSpeedReached();
        void OnHeadHit();
        void OnHitSomething();
        void OnGravityPrevented();
        void OnCrouched();
        void OnStoodUp();
        void OnStandPrevented();
        void OnStartedCrouching();
        void OnStartedStanding();
        void OnFirstJump();
        void OnSecondJump();
        void OnStaminaCapped();
        void OnStaminaReachedZero();
        void OnSprintStarted();
        void OnCooldownStarted();
        void OnCooldownDone();

        // Provides the functionality when AddVelocityForPhysicsTimestep is used
        void OnSceneSimulationStart(float physicsTimestep);
        AzPhysics::SceneEvents::OnSceneSimulationStartHandler m_sceneSimulationStartHandler;
        AzPhysics::SceneHandle m_attachedSceneHandle = AzPhysics::InvalidSceneHandle;
        bool m_addVelocityForTimestepVsTick = true;
        float m_physicsTimestepScaleFactor = 1.f;

        // Velocity application variables
        AZ::Vector2 m_applyVelocityXY = AZ::Vector2::CreateZero();
        AZ::Vector3 m_prevTargetVelocity = AZ::Vector3::CreateZero();
        AZ::Vector3 m_prevPrevTargetVelocity = AZ::Vector3::CreateZero();
        AZ::Vector2 m_scriptTargetVelocityXY = AZ::Vector2::CreateZero();
        AZ::Vector3 m_addVelocityWorld = AZ::Vector3::CreateZero();
        AZ::Vector3 m_addVelocityHeading = AZ::Vector3::CreateZero();
        AZ::Vector2 m_prevTargetVelocityXY = AZ::Vector2::CreateZero();
        AZ::Vector2 m_prevApplyVelocityXY = AZ::Vector2::CreateZero();
        AZ::Vector2 m_correctedVelocityXY = AZ::Vector2::CreateZero();
        float m_velocityCloseTolerance = 1.f;
        bool m_instantVelocityRotation = true;
        bool m_velocityXYIgnoresObstacles = true;
        bool m_gravityIgnoresObstacles = false;
        bool m_posZIgnoresObstacles = true;
        bool m_jumpAllowedWhenGravityPrevented = true;
        bool m_hitSomething = false;
        bool m_gravityPrevented[2] = {false, false};

        // Determines whether the character's X&Y target velocity
        // will be set the request bus (script), in effect the entire time this variable is true
        bool m_scriptSetsTargetVelocityXY = false;

        // Angles used to rotate the camera
        float m_cameraRotationAngles[3] = {0.f, 0.f, 0.f};

        // Top walk speed
        float m_speed = 5.f;

        // Used to track where we are along lerping the velocity between the two values
        float m_lerpTime = 0.f;
        float m_totalLerpTime = 0.f;

        // Sprint application variables
        float m_sprintAccelValue = 1.f;
        float m_sprintPrevValue = 1.f;
        float m_sprintVelocityAdjust = 0.f;
        float m_sprintScaleForward = 1.5f;
        float m_sprintScaleBack = 1.f;
        float m_sprintScaleLeft = 1.25f;
        float m_sprintScaleRight = 1.25f;
        float m_sprintAccelAdjust = 0.f;
        bool m_sprintStopAccelAdjustCaptured = false;
        float m_sprintAccumulatedAccel = 0.f;
        float m_sprintPrevVelocityLength = 0.f;
        float m_sprintHeldDuration = 0.f;
        float m_sprintRegenRate = 1.f;
        float m_sprintMaxTime = 120.f;
        float m_sprintCooldown = 0.f;
        float m_sprintCooldownTime = 1.f;
        float m_sprintPauseTime = (m_sprintCooldownTime > m_sprintMaxTime) ? 0.f : 0.1f * m_sprintCooldownTime;
        float m_sprintPause = 0.f;
        bool m_sprintBackwards = true;
        bool m_sprintWhileCrouched = true;
        bool m_sprintViaScript = false;
        bool m_sprintEnableDisableScript = false;
        bool m_staminaIncreasing = false;
        bool m_staminaDecreasing = false;
        bool m_sprintUsesStamina = true;
        bool m_regenerateStaminaAutomatically = true;

        // Stamina application variables
        float m_staminaPercentage = (m_sprintCooldown == 0.f) ? 100.f * (m_sprintMaxTime - m_sprintHeldDuration) / m_sprintMaxTime : 0.f;

        // Crouch application variables
        float m_crouchDistance = 0.5f;
        float m_crouchTime = 0.2f;
        float m_crouchPrevValue = 0.f;
        bool m_crouching = false;
        bool m_crouched = false;
        bool m_standing = true;
        float m_cameraLocalZTravelDistance = 0.f;
        bool m_crouchEnableToggle = true;
        bool m_crouchJumpCausesStanding = true;
        bool m_crouchSprintCausesStanding = false;
        bool m_crouchPriorityWhenSprintPressed = true;
        bool m_crouchScriptLocked = false;

        // Jumping and gravity
        float m_gravity = -30.f;
        bool m_grounded = true;
        AZ::Vector3 m_velocityXCrossYDirection = AZ::Vector3::CreateAxisZ();
        AZ::Vector3 m_prevVelocityXCrossYDirection = AZ::Vector3::CreateAxisZ();
        AZ::Vector3 m_velocityZPosDirection = AZ::Vector3::CreateAxisZ();
        bool m_velocityXCrossYTracksNormal = true;
        AZ::Vector3 m_sphereCastsAxisDirectionPose = AZ::Vector3::CreateAxisZ();
        AzPhysics::CollisionGroups::Id m_groundedCollisionGroupId = AzPhysics::CollisionGroups::Id();
        AzPhysics::CollisionGroup m_groundedCollisionGroup = AzPhysics::CollisionGroup::All;
        AZStd::vector<AzPhysics::SceneQueryHit> m_groundHits;
        AZStd::vector<AzPhysics::SceneQueryHit> m_groundCloseHits;
        float m_maxGroundedAngleDegrees = 30.f;
        bool m_scriptGrounded = true;
        bool m_scriptSetGroundTick = false;
        bool m_groundClose = true;
        bool m_scriptGroundClose = true;
        bool m_scriptSetGroundCloseTick = false;
        float m_airTime = 0.f;
        float m_jumpInitialVelocity = 6.f;
        float m_jumpSecondInitialVelocity = 6.f;
        bool m_jumpHeld = false;
        bool m_jumpReqRepress = true;
        float m_applyVelocityZ = 0.f;
        float m_applyVelocityZCurrentDelta = 0.f;
        float m_applyVelocityZPrevDelta = 0.f;
        float m_correctedVelocityZ = 0.f;
        float m_capsuleRadius = 0.3f;
        float m_capsuleHeight = 1.8f;
        float m_capsuleCurrentHeight = 1.8f;
        // The grounded sphere cast offset determines how far below the character's feet the ground is detected
        float m_groundedSphereCastOffset = 0.001f;
        // The ground close sphere cast offset determines how far below the character's feet the ground is considered to be close
        float m_groundCloseSphereCastOffset = 0.5f;
        // The sphere cast jump hold offset is used to determine initial (ascending) distance of the of the jump
        // where the m_jumpHeldGravityFactor is applied to the gravity
        float m_jumpHoldDistance = 0.8f;
        // The value of 41.5% was determined to work well based on testing
        float m_groundSphereCastsRadiusPercentageIncrease = 41.5;
        float m_jumpHeldGravityFactor = 0.1f;
        // The m_jumpMaxHoldTime is computed inside UpdateJumpMaxHoldTime()
        float m_jumpMaxHoldTime = m_jumpHoldDistance / ((m_jumpInitialVelocity + sqrt(m_jumpInitialVelocity*m_jumpInitialVelocity + 2.f*m_gravity*m_jumpHeldGravityFactor*m_jumpHoldDistance)) / 2.f);
        float m_jumpCounter = 0.f;
        float m_jumpFallingGravityFactor = 0.9f;
        bool m_doubleJumpEnabled = false;
        bool m_secondJump = false;
        bool m_jumpHeadIgnoreDynamicRigidBodies = true;
        bool m_headHit = false;
        bool m_headHitSetsApogee = true;
        AzPhysics::CollisionGroups::Id m_headCollisionGroupId = AzPhysics::CollisionGroups::Id();
        AzPhysics::CollisionGroup m_headCollisionGroup = AzPhysics::CollisionGroup::All;
        AZStd::vector<AZ::EntityId> m_headHitEntityIds;
        float m_jumpHeadSphereCastOffset = 0.1f;

        // Variables used to determine when the X&Y velocity should be updated
        bool m_updateXYAscending = true;
        bool m_updateXYDecending = true;
        bool m_updateXYOnlyNearGround = false;

        // These default values work well, depending on OS mouse settings,
        // assuming the event value multiplier is 1.0
        float m_pitchSensitivity = 0.0035f;
        float m_yawSensitivity = 0.0035f;

        // Rotation-related variables
        float m_currentHeading = 0.f;
        bool m_scriptSetcurrentHeadingTick = false;
        float m_currentPitch = 0.f;
        AZ::Quaternion m_newLookRotationDelta = AZ::Quaternion::CreateZero();
        float m_rotationDamp = 30.f;
        bool m_cameraSlerpInsteadOfLerpRotation = true;
        bool m_updateCameraYawIgnoresInput = false;
        bool m_updateCameraPitchIgnoresInput = false;
        float m_cameraPitchMaxAngle = AZ::Constants::HalfPi;
        float m_cameraPitchMinAngle = -AZ::Constants::HalfPi;

        // Used when a script wants to update the camera angle via the Request Bus or a gamepad
        bool m_rotatingPitchViaScriptGamepad = false;
        bool m_rotatingYawViaScriptGamepad = false;

        // Acceleration lerp movement
        float m_accel = 30.f;
        float m_jumpAccelFactor = 0.25f;
        bool m_accelerating = false;

        // Deceleration factor
        float m_decel = 1.5f;
        float m_opposingDecel = 2.f;
        float m_decelerationFactor = m_decel;
        bool m_decelerationFactorApplied = false;
        bool m_opposingDecelFactorApplied = false;

        // Movement scale factors
        // assuming the event value multipliers are all +1.0
        float m_forwardScale = 1.f;
        float m_backScale = 0.75f;
        float m_leftScale = 1.f;
        float m_rightScale = 1.f;
        float m_sprintAccelScale = 1.5f;
        float m_crouchScale = 0.5f;
        // This sphere cast determines how far above the charcter's head that an obstruction is detected
        // for allowing them to uncrouch
        float m_uncrouchHeadSphereCastOffset = 0.1f;
        bool m_standPrevented = false;
        bool m_standPreventedViaScript = false;
        AzPhysics::CollisionGroups::Id m_standCollisionGroupId = AzPhysics::CollisionGroups::Id();
        AzPhysics::CollisionGroup m_standCollisionGroup = AzPhysics::CollisionGroup::All;
        AZStd::vector<AZ::EntityId> m_standPreventedEntityIds;
        bool m_standIgnoreDynamicRigidBodies = true;

        // Event value multipliers
        float m_forwardValue = 0.f;
        float m_backValue = 0.f;
        float m_leftValue = 0.f;
        float m_rightValue = 0.f;
        float m_yawValue = 0.f;
        float m_pitchValue = 0.f;
        float m_sprintValue = 1.f;
        float m_crouchValue = 0.f;
        float m_jumpValue = 0.f;

        // Event IDs and action names
        StartingPointInput::InputEventNotificationId m_moveForwardEventId;
        AZStd::string m_strForward = "Forward";
        StartingPointInput::InputEventNotificationId m_moveBackEventId;
        AZStd::string m_strBack = "Back";
        StartingPointInput::InputEventNotificationId m_moveLeftEventId;
        AZStd::string m_strLeft = "Left";
        StartingPointInput::InputEventNotificationId m_moveRightEventId;
        AZStd::string m_strRight = "Right";
        StartingPointInput::InputEventNotificationId m_rotateYawEventId;
        AZStd::string m_strYaw = "Yaw";
        StartingPointInput::InputEventNotificationId m_rotatePitchEventId;
        AZStd::string m_strPitch = "Pitch";
        StartingPointInput::InputEventNotificationId m_sprintEventId;
        AZStd::string m_strSprint = "Sprint";
        StartingPointInput::InputEventNotificationId m_crouchEventId;
        AZStd::string m_strCrouch = "Crouch";
        StartingPointInput::InputEventNotificationId m_jumpEventId;
        AZStd::string m_strJump = "Jump";

        // Array of action names
        AZStd::string* m_inputNames[9] = {
            &m_strForward, &m_strBack,
            &m_strLeft, &m_strRight,
            &m_strYaw, &m_strPitch,
            &m_strSprint, &m_strCrouch,
            &m_strJump
        };

        // Map of event IDs and event value multipliers
        AZStd::map<StartingPointInput::InputEventNotificationId*, float*> m_controlMap = {
            {&m_moveForwardEventId, &m_forwardValue},
            {&m_moveBackEventId, &m_backValue},
            {&m_moveLeftEventId, &m_leftValue},
            {&m_moveRightEventId, &m_rightValue},
            {&m_rotateYawEventId, &m_yawValue},
            {&m_rotatePitchEventId, &m_pitchValue},
            {&m_sprintEventId, &m_sprintValue},
            {&m_crouchEventId, &m_crouchValue},
            {&m_jumpEventId, &m_jumpValue}};
    };
}
