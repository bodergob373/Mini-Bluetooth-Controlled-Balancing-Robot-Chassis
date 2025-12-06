---
Title: Mini Bluetooth-Controlled Balancing Robot Chassis
Author: Jonathan Itoh
Created On: 2025/12/06
Total Time: 21h
---



# 2025/12/2: Research and Choosing Components: 3h
I originally planned for the robot to use brushless RC aircraft motors with planetary gearboxes that spin the wheels through pulleys. I started looking for cheap motors and found A2212 motors. For encoders, I found a magnetic encoder that can be mounted near a small magnet attached to the motor shaft. However, after some checking, I realized that finding cheap, precise ESCs that can handle enough current would be difficult and the whole gearbox + pulleys would create a lot of slop in the wheels, so I scrapped the whole idea. After seeing the motors in videos of balancing reaction wheel cubes, I found out about Nidec 24H BLDC motors, which already have built-in optical encoders and ESCs. They have less power, so I will need to downsize the robot. Even though they have lower RPM, I will still need some sort of gearbox. I decided on putting inverted ring gears inside the wheels that mesh with the spur gears on the motors for decent reduction. For batteries and the microcontroller, I decided to use some sort of ESP32 and 3S LiPo.

Nidec 24H055M020 with a D-shaft

<img width="245" height="206" alt="image" src="https://github.com/user-attachments/assets/df341ff3-6234-4b10-90b1-372af484e0ba" />



# 2025/12/2: CAD 1: 3.5h
I began designing the robot in Onshape starting with the drive system. For the gears, I got a premade configurable planetary gear feature, set the planet number to 1, deleted the sun gear, and set the tooth count so that it would be a 1:4 ratio.

<img width="537" height="488" alt="image" src="https://github.com/user-attachments/assets/946d4a0c-95ca-4f0f-b76a-60ebed41911d" />

Most of the robot frame will be designed around the shape of the motors, so I found dimensions and designed a simple model and positioned it with the shaft going through the spur gear.

<img width="533" height="565" alt="image" src="https://github.com/user-attachments/assets/b83c6e78-479d-4d81-ae02-85c4f2dee3ad" />

Before I designed the wheel, I needed good-sized ball bearings that are positioned right. It took really long to do this because the gears needed clearance and I need to make sure that the wheel would wiggle as little as possible. I kept switching between small, wide bearings that fit inside the ring gear and large, narrow bearings that go beside it. Both wouldn't fit right, so I decided to use two small, narrow bearings per wheel. This would allow them to go fit on both sides of the spur gear and provide a lot of support for the wheel. I would be able to connect the outside of both bearings to the motor case and press in a plastic shaft connected to the wheel.

<img width="618" height="590" alt="image" src="https://github.com/user-attachments/assets/b953b826-bdcf-429c-ad3d-9400524dfe52" />



# 2025/12/3: CAD 2: 7h
I raised the motor to make the gears larger so that the spur gear could fit on the motor shaft and the bearings would have some more space. Then, I designed the wheel. I added side ridges on the wheel so that wide rubber bands can be stretched around the wheel for enough grip. I also put a hole through the spur gear.

<img width="382" height="538" alt="image" src="https://github.com/user-attachments/assets/75828029-1bbd-4316-a42e-8b6f748b7a51" />
<img width="515" height="587" alt="image" src="https://github.com/user-attachments/assets/77a53bf2-bbf4-4a9e-add1-0cd4702962f5" />

For the motor case, I first made a tube around both bearings. To prevent the outer bearing from getting pushed in too far, I put a spacer between.

<img width="708" height="660" alt="image" src="https://github.com/user-attachments/assets/02042eed-0faf-4b40-ab7d-0a84645c4d92" />

Then, I made a thin case that fits around the entire motor and put holes through for the screws. I didn't want the bearing mount to be floppy, so I made the motor case thicker there. The motor also has a big chunk that sticks out the side for the plug, so I cut that out of the case too. So that the motors can be put into the case, the back would have to be open and the entire wheel + case could be screwed onto the robot base. I added a mounting plate for that and put fillets everywhere to make everything smooth.

<img width="656" height="595" alt="image" src="https://github.com/user-attachments/assets/23951b72-7209-4ce1-96b3-996160aa6924" />

Like the motor case, the robot base would have to be designed around the huge battery. To get near the motor's 12V input, I will need a 3s LiPo. It also needs to be thin otherwise the entire robot is gonna be either super wide or extra tall and have some wasted space between the motors. Finding a cheap battery that meets these requirements and has decent capacity took a while, but I eventually found one.

<img width="351" height="293" alt="image" src="https://github.com/user-attachments/assets/57464e88-350d-4441-ad90-71c8ad70f87d" />

I made the battery case with mounts for connecting the motor assembly. It's only half of the case because it will be mirrored later.

<img width="616" height="673" alt="image" src="https://github.com/user-attachments/assets/eeac6b67-070c-44f2-97c4-daca5e2254ab" />

Next, I needed to add the microcontroller, but I had to choose what ESP32 to use. I originally picked a WEMOS Lolin32, but later decided to use a more generic 30-pin ESP32 devboard with mounting holes.

<img width="462" height="300" alt="image" src="https://github.com/user-attachments/assets/df31f737-aeaa-4adf-b46e-6aef11295e65" />
<img width="708" height="488" alt="image" src="https://github.com/user-attachments/assets/7fa67407-4c6d-4f7d-8b22-fd697eaa28a4" />



# 2025/12/4: Finished CAD: 4h
It was difficult to find a good place to mount the ESP. The only usable space on the robot base is on the front and back, so I added protrusions on the back that screws can tap into.

<img width="355" height="484" alt="image" src="https://github.com/user-attachments/assets/96429d38-1e34-451c-901a-49b8757bea43" />

For the accelerometer, I will use a BNO055 breakout module because it has built-in orientation calculation, which will simplify the code and probably be more accurate. Because it has no holes for screws but is pretty flat, I added a gap in the robot base that the board can be wedged into.

<img width="537" height="623" alt="image" src="https://github.com/user-attachments/assets/2e97fe52-ff60-404c-a8a8-8aab0e209d08" />

I also need a buck converter to supply power to the microcontroller, so I found a cheap LM2596 breakout board that meets the power requirements. It has two holes for screws, so I added four more protrusions on the front that allow it to be mounted either up or down.

<img width="591" height="714" alt="image" src="https://github.com/user-attachments/assets/d83f0128-c54b-4d45-b54e-a00c60c50d5a" />

The parts are finally done. I mirrored the drive module to the other side and moved the components to the right spots.

<img width="762" height="763" alt="image" src="https://github.com/user-attachments/assets/427841e9-37ca-40db-8ccb-0a93d590c4ae" />
<img width="701" height="681" alt="image" src="https://github.com/user-attachments/assets/6b6dbf4d-7bcd-4986-85b2-fb2dfa456a61" />



# 2025/12/5: Added Tolerances: 2h
To prepare for printing, I added configurable tolerances for the parts so that parts like the bearings can fit in and the gears can mesh well. I did this by creating variable tables and using those values in the sketch dimensions and features. In order to do it well, I had to organize and separate some sketches and features.

<img width="613" height="595" alt="image" src="https://github.com/user-attachments/assets/90057bb3-9a48-49e7-b8f5-5c4b7b79fb56" />



# 2025/12/5: Wiring Diagram: 1h
I made the wiring diagram. It went smoothly until I found out that there should be capacitors on the buck converter output to protect the ESP32 from current spikes. I also had to research what pins to use on the GY-BNO055 IMU.

<img width="768" height="608" alt="image" src="https://github.com/user-attachments/assets/5446e40a-4b66-4b60-8fa2-7ef0008c38c9" />



# 2025/12/5: Generated the Code: 0.5h
I'm running out of time, so I got AI-generated code for the robot. I did have to research how the motors need to be controlled, though. It would probably take me days to research, code, and test the robot's control loop myself anyways. I have no idea if the code will work until I build the robot and test it.

<img width="748" height="683" alt="image" src="https://github.com/user-attachments/assets/9943f25f-54c2-4e04-8e7c-e28bb24a8bac" />
