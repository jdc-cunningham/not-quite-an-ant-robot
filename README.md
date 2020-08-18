# About
My first legged robot. This was not really designed in terms of using math with regard to torque on servos/current draw/etc... as a result it works best on flat surfaces. The motion of the body is also not great since it can't really lift the legs straight up, rather just swing them out then in an arc to move. At this time I'm still working on the control system by phone, I have an ESP8266-01 and it has a websocket server that my phone connects to, then by serial between the ESP and Arduino I can send commands to run specific gaits to move the robot. At the moment I only have some forward gaits, I am still working on improving/writing better "abstractions" for the code eg. passing in an array of servos/ranges into a function to move the servos at the same time. Right now I just have a bunch of loops as a proof of concept.

This is not intended to be replicated, I mean all the parts are here and I'll provide estimates on print but it's not a good design.

This project has been in progress for at least a week, I don't have a repo history because I published my WiFi SSD credentials in the original private repo.

# The vision/concept

![drawing of concept](./robot/sketches/concept.PNG)

Later on it turns out that having a controller like this while cool is also not practical as the robot is so slow, I'll still build it but it'll be like a "heading hold" type of control.

![current build](./github-stl-view.gif)

I did just throw a thing on top to hold the electronics, ideally the CG would be lower, there is clearance below the body, especially since now it's not intended to work on carpet which mine is a little deep eg. `1/2 in` long threads.

While I did design the legs like this(back set not mirrored), they are actually technically "backwards"/not symmetrical... so it has a forward-cg to compensate.

![current build side](./side-view--slow-gait.gif)

It has a middle servo pretty much for balance, when it moves forward the middle servo lifts up the middle legs. Anyway with this design as a result I can't do the tripod-gait, I have some kind of wave gait going on. It is nuts how much current all the servos pull. I had to use a 2A wall power supply and hardly any of my batteries would work(too heavy/not enough current).

![current build back view](./initial-walking--back-view.gif)

Here the servos are not moving very fast(`10ms delay`) and a 2 second overally delay between the forward motion gait see [here](./robot/code/test/all_servos/all_servos.ino).

# Parts list

- 9g servo x9
- Arduino Nano
- ESP8266-01
- 5V linear regulator
- 3.3V linear regulator x2
- 10K resitor
- UBEC for battery pack
- 9.6v 8cell 2400mAh NiMh battery pack
- solderable breadboards
- breadboards
- breadboard wires
- 3D printer/filament
- hot/super glue

# Feature Completion

- [x] physical body
- [x] basic socket to serial communication
- [ ] rest of the gaits
    - [ ] backwards
    - [ ] sideways (crab)
    - [ ] rotate
    - [ ] roll
- [ ] mobile controller
- [ ] add IMU (9-axis)
- [ ] add ultrasonic sensor on front

# Print times (0.2mm quality 20% infill)
- 49 mins main servo mount for swivel arms
- 2 hrs 42 mins middle lift legs
- 4 hrs 20 mins top group
- 3 hrs 14 mins test stand
- 1 hr 29 mins outer pitch legs
- 1 hr 26 mins 1 swivel arm
- 1 hr 34 mins main stick with holes

# Software

The parts were designed with Google SketchUp. I used a plugin to export the STL file(as well as a solid part inspector plugin) then used Cura to slice the parts. Take note of parts that need supports, you have to turn that on in Cura. Parts are printed with a Creality Ender 3 Pro.

# Warning

The servo horn spline I have here is bad, they slip. I traced/made my own from a photo I took. I ended up having to use long screws and super glue to try and make them not slip. Also the design is generally bad where the servos are directly holding the load vs. just transfering motion. And overall the design is bad as I mentioned with how it can move. I think you need more servos but it's nuts thinking each leg would have at least 3 servos and a true hexapod would have 18 servos right there.

# Thoughts

Overall it is a fun project, learned a lot. It has a ways to go code wise and will serve as a platform for other work.
