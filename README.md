# Unreal Sandbox
Unreal Sandbox is a project that aims to showcase the capabilities of Unreal Engine 5. It is a sandbox environment that allows users to explore and interact with various features of Unreal Engine 5 focusing on character related mechanics. The project is built using C++ and Blueprints.

## Features
### Camera
Project includes third person camera attatched with spring arm to used character. Camera reacts to mouse movement by applying appropriate rotations.
```
void ADungeonCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}
```
Inupt is handled using Enhanced Input system.

### Character Movement
Character movement includes keybord controls for moving forward, backward, left, right and jumping. All inputs take advantage of Enhanced Input system.
Action implementation is done in C++ same as for camera.
```
void ADungeonCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D DirectionValue = Value.Get<FVector2D>();

	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0, ControlRotation.Yaw, 0);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, DirectionValue.Y);
	AddMovementInput(Right, DirectionValue.X);
}
```
Above code handles all movement aside from jumping. Jumping is handled using default Unreal Engine functionality.
It is worth to mention that charcter movement takes into account character rotation. This means that character will always move in the direction it is facing.

### Animation
Character animation is handled using Animation Blueprint. Animation Blueprint is used to switch between different animations based on character movement.
There are 3 available states:
- Idle - single animation
- Running - single animaton
- Jumping - one animation for jumping and one for falling

### Rigging
Control rig is uded to take advantage of Unreal Engine 5's Inverse Kinematics (IK) system. Control rig is used to create a simple IK system that allows character to interact with the environment.
IK is used to dynamically adjust character's position based on the surface they are standing on. This allows for more realistic movement and interaction with the environment, especially on uneven surfaces.

Rigging is done in multiple stages:
1. Sphere tracing from character's feet to the ground to find the Z offset.
2. Interpolation of the Z offset to create a smooth transition.
3. Setting pelvis z offset to minimum of the two feet.
4. Moving IK feet and pelvis based on offsets.
5. Performing full body IK with root set to pelvis.