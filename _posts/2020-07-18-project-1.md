---
title: 'Inverse Kinematics'
date: 2020-07-18
permalink: /projects/inversekinematics/
tags:
  - robot arm
  - 3d printed
  - arduino
code-block-font-size: \tiny
---

Inverse Kinematic controls designed around an open-source 3d printable robotic arm for implementation in an Arduino control setting.

Robot Arm Inverse Kinematics
======
<br/><img src='/images/armillustration.png' style='width:400px;'>

Controlling individual joints on a robot arm to complete a task is an awkward task to do. Looking at commercial robots, most if not all robotics companies such as Fanuc, Boston Dynamics, and Kuka all implement control systems alongside their robots. This software makes the job of programming the robots a cakewalk compared to what it would have otherwise been. 

This is the premise of my project: implementing my own inverse kinematic algorithm to make controlling a robot arm simple.
<br/><img src='/images/eezybotarm.jpeg' style='width:400px;'>

I chose to print [daGHIZmo's EEZYbotARM](https://www.thingiverse.com/thing:1015238) on my Prusa Mini due to its popularity, control simplicity, and small size making it easy to use. My code involves converting cartesian coordiantes, given by the user into polar coordinates the arduino then forwards to the servos.
<br/><img src='/images/circuit.png' style='width:400px;'>

The first step is to determine the rotators position along the XY plane. By forming a triangle across the surface, the angle for the rotator can be determined:
```cpp
float rotatorAngle = atan(posX / posY) / (6.28318530718) * 360;
	 rotator.write(-rotatorAngle + 90);
```

This step simplifies the 3D problem into a 2D problem that we can then solve with trigonometry. 
<br/><img src='/images/robotarm.png' style='width:400px;'>

I know the location of the base and where the hand should be (the desired coordinate) as well as the lengths of each side. Thus to determine the angles of the shoulder and elbow, I form a triangle whose vertices are the shoulder joint, elbow joint, hand and we solve:
```cpp
// Creation of general units such as directional distances as well as angles
  float dist = sqrt(pow(posX, 2) + pow(posZ, 2) + pow(posY, 2));
  float distXY = sqrt(pow(posX, 2) + pow(posY, 2));
  float orthRad = atan(distXY / posZ);
  float orthDist = sqrt(pow(8, 2) - pow(dist / 2, 2));

  // Creates vertical and horizontal components of the shoulder and outputs as an angle
  float shoulderXY = distXY / 2 - orthDist * cos(orthRad);
  float shoulderZ = posZ / 2 + orthDist * sin(orthRad);
  float shoulderAngle = (atan(shoulderXY / shoulderZ) / 6.28318530718) * 360;
  shoulder.write(shoulderAngle + 50);

  // Creates vertical and horizontal components of the elbow and outputs as an angle
  float elbowDistXY = distXY - shoulderXY;
  float elbowDistZ = posZ - shoulderZ;
  float elbowAngle = atan(elbowDistZ / elbowDistXY) / (6.28318530718) * 360;
  elbow.write(elbowAngle + 90);
```

### Conclusion
The final product of my code can be seen near the end of our robotics team [video](https://drive.google.com/file/d/120xbQWK3byd0JYZZBSJeAWJS28cFzHDw/view?usp=sharing) I made at the start of the year.

Some things I would like to improve upon in the future are:
- Adding a smoothening aspect to reduce the jitterness of the movement
- Extend the code to allow for n number of joints
- Extend the code to apply to arms that implement linear actuators
- Optimize the mathematics involved
