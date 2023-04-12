<!--
GS
https://stackoverflow.com/a/72724753/4561887
-->

## Quick summary:

#### How to avoid drift when self-balancing:

Jump straight down to the "In summary" section below. Here that section is, quoted, for convenience:

> To keep your 2-wheeled robot balanced with*out* letting it drift forward/backward, you should have a _linear velocity_ controller with a command of 0 m/s, rather than just an _angle controller_ with an angle command of 0 deg. Your **linear velocity controller** calculates a desired _acceleration_ which feeds into your **linear acceleration controller**, which calculates a desired _tilt angle, or pitch_, which feeds into your **pitch angle controller**, which adjusts motor throttles to achieve that pitch (using, for example, a PID or LQR controller, or a physics-based controller you can come up with for this inner, self-balancing loop as well). 
> 
> _To achieve your objective you stated, of no longer drifting or rolling forwards, you'd stop there._
> 
> **But, I'd go further:** what if your vehicle has *already* drifted or rolled a little bit, wouldn't you want to move it back to where it started to "undo" that drift?
> 
> Here's how:...[add a _position controller_ too, which feeds into the _velocity controller_]...

Details:


## Physics-based ["cascaded controls"](https://en.wikipedia.org/wiki/PID_controller#Cascade_control), and control systems: the many layers of control

**AKA: a full description of all of the necessary control loops for a robust vehicle controller, including for self-balancing systems like 2-wheeled self-balancing Segway-like robots, or quadcopters/drones.**

In any complicated control system, you have to have multiple layers of controllers. 

From inner-most to outer-most controller, here is what you need:

1. **Pitch angle controller:** In your case, your **inner-most controller** sounds like it is pitch angle: I think you are using an LQR controller to *adjust wheel motor throttle* to control *pitch angle*. You could also use a PID controller for this, _or_ come up with a physics-based feed-forward solution instead, summed with a PID feedback solution to remove error.

    If you make your pitch angle set-point 0 deg, then the robot will stay stationary standing straight up so long as no outside force acts upon it, and so long as it also began at rest. If you push the robot, it will start to translate linearly (ex: move forward or backwards), at the constant velocity you imparted upon it, while maintaining a fixed, upright angle. Essentially, keeping your pitch angle set-point at 0 degrees makes this the same as giving a shove to a motorless ball or cart--it will keep rolling in the direction you push it per Newton's 1st Law of Motion, which is about inertia: an object in motion stays in motion.

1. **Linear acceleration controller:** You need to add an **outer controller** where you *adjust pitch angle* to control *linear acceleration* (forwards or backwards). 
    
    Think about it like this: this is a physics problem: the more a 2-wheeled Segway-like robot is tilted forward, the faster gravity causes it to "fall forward". The faster it "falls forward", the faster you must drive those wheels to try to get those wheels back underneath it, to make it maintain a fixed tilt angle rather than continuing to tilt further until it hits the ground. Moving the wheels underneath it to prevent it from falling over causes it to accelerate in that direction. 
    
    For a tilted vehicle at a fixed altitude (for air vehicles; or on a level surface, for ground vehicles) and at a fixed tilt angle, the linear acceleration, `a`, is: **`a = g*tan(theta)`**, where `g = acceleration due to gravity = 9.81 m/s^2`, and `theta = tilt angle`. Here is a "Balance of Forces" diagram (side view: down is towards the ground and up is towards the sky) I just drew:

    [![Balance of forces diagram][1]][1]

    Solve for `theta` (tilt angle), and you get: **`theta = atan(a/g)`**.

    So, `a` in a translational (forwards or backwards) direction is in units of `m/s^2`. Over time (`s`), this translational acceleration results in a certain translational velocity (`m/s^2 * s = m/s`). So, if you hold it tilted for a moment, let it accelerate, and then stand it back up straight again, you'll now be continuing forward at a fixed velocity, assuming level ground and no friction. That's what's happening to you when someone pushes or kicks it! To counter this translational _velocity_, you'll need a _velocity controller_ which applies the necessary _acceleration_ in the opposite direction in order to stop the vehicle's motion. 

1. **Linear velocity controller:** The next controller is a velocity controller. You need to set a desired velocity (ex: `0 m/s` to stop the vehicle). In this controller, you *adjust linear acceleration* to control *linear velocity*. 

    You can then set a tuning parameter, `tau [sec]`, which is the _time constant_ over which period you'd like to achieve your desired velocity. Tune this to be very small for a fast response, and for systems with low inertia, and tune it to be very large for a slow response, and for systems with high inertia. If you tune it too low, the system will have bad jitter and respond to noise--kind of like setting your control loop too fast or your derivative gain too high in a PID controller. If you tune `tau` too high, the system will be very slow and sluggish to respond. Essentially, `tau` is like a "gain" tuning parameter, where `response_gain = 1/tau`. Therefore, a large time constant, `tau`, results in a slow response or "low gain", and a small `tau` results in a fast response or "high gain".

    You can see my `tau` value in my quadcopter flight controller circled in yellow here:

    [![enter image description here][2]][2]

    ([video link to this moment in time](https://youtu.be/H5kXzpPFdII?t=20)). As shown in the image, it is currently set to `0.75 sec`. My notes for that parameter in the image above say:

    > time_const, tau (sec) (gain is proportional to 1/tau): `0.75`
    > 
    > <--(increase for "lower gain," decrease for "higher gain")

    This "linear velocity controller" is therefore another layer with a physics-based controller. You need the physics equation of motion for this: `dv [m/s] = a [m/s^2] * dt [sec]`. Solve for `a` and you get `a = dv/dt`. The time period, `tau`, over which you'd like to accomplish this is your `dt` (time change, in sec), resulting in **`a = dv/tau`**. 

    ### _Full example calculation_ up to this point:

    So, if your actual velocity is `2.5 m/s` and your desired velocity is `0 m/s`, then the desired velocity change, `dv`, that you need is `dv = 2.5 m/s - 0 m/s = 2.5 m/s`. You ultimately need to tune `tau` as a tuning parameter, through experimentation or simulation and modelling, or both. Let's assume you have chosen an initial `tau` value of `tau = 2 sec`. Then, the necessary acceleration you need to achieve this velocity change over that time period `tau` is **`a = dv/dt = dv/tau = 2.5m/s / 2 sec = 1.25 m/s^2`**. 

    This liner acceleration required by your **linear velocity controller** here is your input to the **linear acceleration controller** above. Solve for pitch angle, `theta`, from the **linear acceleration controller** above: **`theta = atan(a/g) = atan(1.25 m/s^2 / 9.81 m/s^2) = atan(0.12742) = 0.1267 rad x 180 deg/pi rad = 7.26 deg`**. So, input `7.25 deg` (with the correct sign, per your situation) as your set-point into your **pitch angle controller** in order to begin decelerating from 2.5 m/s to 0 m/s over a time period, tau, of 2 sec. 

    Run the inner control loop as fast as is reasonable, perhaps 50 to 500 Hz. 

    Run the outer control loops as fast as is reasonable, perhaps 25 to 50 Hz. 

    Note that the farther "outside" that your control loop is, the slower you can run your control loop. Self-driving cars, for instance, run their outer-most control loops at around 10 Hz, partly since this is good enough, and partly since the computational complexity is so high that this is all the computers can do.

    ### _In summary_

    To keep your 2-wheeled robot balanced with*out* letting it drift forward/backward, you should have a _linear velocity_ controller with a command of 0 m/s, rather than just an _angle controller_ with an angle command of 0 deg. Your **linear velocity controller** calculates a desired _acceleration_ which feeds into your **linear acceleration controller**, which calculates a desired _tilt angle, or pitch_, which feeds into your **pitch angle controller**, which adjusts motor throttles to achieve that pitch (using, for example, a PID or LQR controller, or a physics-based controller you can come up with for this inner, self-balancing loop as well). 

    _To achieve your objective you stated, of no longer drifting or rolling forwards, you'd stop there._

    **But, I'd go further:** what if your vehicle has *already* drifted or rolled a little bit, wouldn't you want to move it back to where it started to "undo" that drift?

    Here's how: add yet another layer of control as a _linear position controller_ outside your _velocity controller!_ 

4. **Linear position controller:** You will *adjust linear velocity* over time to control *linear position*. With your wheel encoders, you can figure out how far you've gone, and control *position* to get the robot to return back to where it started. Or, you can simply command any arbitrary position to have it drive certain distances and navigate around the room. This is another feed-forward controller based on simple physics/math, where the equation of motion is simply `v*t = d`, where `v [m/s]` is velocity, `t [sec]` is time, and `d [m]` is distance. 

    There are a variety of ways to do this. 

    If your goal is to **go to a position and stop:**

    One way is to command a certain velocity for a given time in order to achieve a desired distance. Ex: command 0.5 m/s for 3 seconds to go `0.5 m/s * 3 sec = 1.5 m`. Then, command 0 m/s to stop at that point. You might have to use some empirical data and heuristics where you command the 0 m/s velocity a little early to give the vehicle time to respond and stop right where you want it rather than overshooting. 

    This might be called a "tick controller" (I'm inventing this term right now), where you write a function to drive N seconds at X velocity to achieve Y encoder "ticks" of distance movement in that direction, with empirical adjustments as necessary. You could tweak this controller to even be able to handle ticks as small as 1 encoder tick using a rapid velocity pulse for a short amount of time, so as to get to the *exact* position you want to be at as you get close to your commanded position. Each control loop iteration, you pass a new value of the desired number of distance encoder "ticks" to move, based on where you are now and where you want to be. The interesting thing about this physics-based "feed-forward" controller, therefore, is that it's implicitly also a type of "feedback" controller, which is weird. Some pedantic academics out there have probably come up with some special ways of talking about this, perhaps even with some special terms for it, but I don't know what they are.

    An alternative approach would be to command a fixed velocity, ex: 0.5 m/s, until you are within some minimum distance error bound, say: 0.5m, then switch to a PID feedback controller which commands a _velocity_ based on _position error_. This way, as your _position error_ approaches zero, your _commanded velocity_ will also approach zero, which makes sense. If your PID gains are strong enough, or conversely if your position error is large enough, this is the same thing as just using a PID feedback controller on position where you saturate the velocity command by clipping it to a fixed maximum value. Of course, even for weak gains, at some large enough distance error, the commanded velocity would still hit the maximum allowed (saturated) value and get clipped.

    If your goal is to **keep a fixed velocity while following a 2D path at this velocity:**

    Then you could set your velocity controller to a fixed value while changing your commanded heading to always point down the path. I do this using a "lead point" technique, or "pure pursuit" algorithm, as demonstrated in my [3 videos here](https://github.com/ElectricRCAircraftGuy#heres-one-of-my-favorite-projects-ive-ever-done-autonomous-quadcopter-flight-controller-i-wrote-myself): [1](https://www.youtube.com/watch?v=LjuPA43HceQ), [2](https://www.youtube.com/watch?v=wY3oh2GIfCI), [3](https://www.youtube.com/watch?v=H5kXzpPFdII&t=35s). Since my vehicle is a hovering quadcopter drone, however, I have the luxury of changing my commanded _thrust vector_ rather than my _heading_, so I can just command a fixed heading if I want (ie: keep the drone always pointing North) while changing the commanded thrust vector to move in different 2D (x-y) directions.

    **Getting exact measurements:**

    While integrating velocity over time will obtain distance, numerical integration or estimating is best used in this case to calculate commanded velocity outputs for the feed-forward parts of your _controller_ which will output a desired velocity _command_ for a certain duration of _time_ in order to achieve a desired _change in position_. 

    With your wheel encoders, you can measure the *actual* distance traveled instead of *estimating* it using velocity over time. 

    If you do need to _estimate_ position traveled by integrating _velocity_ over _time_, however, you should use _trapezoidal_ numerical integration, as I explain here: [Numerical derivation and integration in code for physics, mapping, robotics, gaming, dead-reckoning, and controls](https://stackoverflow.com/a/72162992/4561887), since it is more accurate than rectangular integration and is trivial to implement. Again, for numerical integration, the simple idea is that `velocity [m/s] * time [s] = distance [m]`.

    Again, remember that you shouldn't necessarily integrate to _estimate_ the _actual_ distance traveled. Rather, _measure_ the actual distance traveled by counting encoder ticks since that's a more-precise measurement.


**How to measure encoder "ticks" or distance moved:**

_Remember that for all these controllers:_
1. You read the **wheel encoders** to determine wheel motion. 
1. If you don't have wheel encoders, read the motor **hall effect sensors** instead. They have worse resolution, but can be used in place of encoders. 
1. If you don't have hall effect sensors, but you are using 3-wire (3 phase) **brushless motors**, then you can read the **back-EMF commutation waveforms or cycles** instead, to read the commutation frequency and thereby estimate motor RPM (Rotations Per Minute). You can count commutation cycles to get an estimate of position, like from an encoder or hall effect sensors, but with less resolution still. 
    1. This is complicated, but can be done in software via a microcontroller such as Arduino (I've done it). What you need to do is wire up ground on an Arduino Nano to your vehicle's battery ground. Then, run another wire to any of the 3 brushless motor's phase wires, through a diode clipping circuit to reduce the commutation voltage from V\_bat peak to \~4.5V peak, and then into Arduino pin D8, which is the _Input Capture_ pin for the ATMega328 microcontroller. Use Input Capture in software, via interrupts, to read all pulses on the phase. 
    1. Here is what those pulses look like ([image source](https://www.rcgroups.com/forums/showthread.php?952523-too-long-battery-wires-will-kill-ESC-over-time-precautions-solutions-workarounds)): [![enter image description here][3]][3]. 
    1. The little pulses are the 8 KHz\~16 KHz motor PWM throttle pulses. You need to digitally filter these out in software. The big trapezoidal commutation frequency waves are the commutation waveforms, and _their frequency is directly proportional to your motor RPM_. Hence, you can measure commutation frequency to calculate motor rotational frequency, or RPM. The relationship is scaled by the number of permanent magnetic poles in the brushless motor. I'd have to dig up my notes, but I believe the equation is something like this: `RPM = freq_commutation/(num_magnetic_poles*120)`. The point is, the commutation frequency can be read in software by a microcontroller's input capture pin, and then converted to motor rotational velocity via a simple equation based on the number of permanent magnetic poles in the motor. Note that higher-end motor drivers (ESCs--Electronic Speed Controllers) use sinusoidal commutation waveforms, which are more efficient and have better torque, instead of trapezoidal, but the commutation frequency principal is the same.


The **types of controllers you will be using** in your case are these, again, from inner-most to outer-most controller:

1. **Pitch angle controller:** LQR (from what you said). You could also use PID.
1. **Linear acceleration controller:** A physics-based feed-forward (the bulk of the control input). 
    1. Optionally, add a PID feedback on the error of actual vs commanded linear acceleration to tune it so that the actual linear acceleration approaches the commanded linear acceleration. 
    1. Sum the outputs from the feed-forward physics-based controller and from the PID feedback controller.
1. **Linear velocity controller:** A physics-based feed-forward (the bulk of the control input for low speeds). 
    1. Optionally, add another layer of physics control to compensate for _air resistance as velocity increases_. `Drag [N] = C_D*q*A`, where `C_D [unitless]` is your experimental drag coefficient for your particular vehicle's shape properties and how that shape interacts with the fluid of interest (air in our case), `q [N/m^2] = dynamic pressure = 1/2 * rho * v^2`, where `rho [kg/m^3]` is air density, and `v [m/s]` is velocity, and `A [m^2]` is _frontal area_ (which is geometry-based, since it decreases the more the robot is tilted).  

        Let's verify the drag equation with a quick units check: `Drag [N = kg*m/s^2] = C_D [no units] * q [kg/m^3 * m^2/s^2 = kg*m*m/(m^3*s^2) = kg*m/s^2 * m/m^3 = N/m^2] * A [m^2] = [N/m^2 * m^2 = N]` Yep! It comes out correctly: the right side of the drag equation (`C_D*q*A`) does indeed have units of Newtons (`[N]`). I stated the equation correctly.  

        THEN, on top of that extra physics-based layer which accounts for air resistance as the robot speeds up:
    1. Optionally, add a PID feedback on error of actual vs commanded linear velocity to tune it so that the _actual_ linear velocity approaches the _commanded_ linear velocity. 
    1. Sum the outputs of all controllers. 
1. **Linear position controller:** A simple "physics-based" (integration of velocity with respect to time) feed-forward controller to achieve a desired position change in a given amount of time. 
    1. To go to a desired position and stop:
        1. Optionally, add a PID feedback controller (commanding a velocity based on the position error) on actual vs desired _position_. Keep a total +/- wheel encoder displacement count, and seek to zero it--the larger the position or distance "error", the stronger the commanded linear velocity towards the target point should be.
        1. You may run a physics-based feed-forward controller followed by a PID feedback controller when your position error is within a certain bound, OR just use a well-tuned "tick controller" as I described above, OR, _only_ use the PID feedback controller if you like, saturating the maximum commanded velocity output of course to some reasonable level.
    1. To keep a fixed velocity while following a 2D path:
        1. You should command a fixed velocity while continually moving an aim-point down a target path, continually adjusting your commanded heading to get you to go in the right direction. Consider adjusting velocity dynamically based on things such as commanded turn radius to 1) keep from tipping over, and 2) allow you to follow difficult parts of the path easier. Tuning the lead point forward-projected distance down the _desired path_ is a type of low-pass filter on the sharpness of the _commanded path_. This may sound a bit abstract, but see my 3 quadcopter videos above and I think you'll see what I mean. 
            1. Ex: in this image from [this video at this point in time](https://youtu.be/LjuPA43HceQ?t=111), the blue path is an overhead view of the _desired path_ for my quadcopter, and the red path is the _commanded path_, which is essentially low-pass-filtered by the _lead-point-distance_ as a tuning parameter. The _shorter_ the lead point distance, the more closely the red _commanded path_ will overlay the blue _desired path_, and the _longer_ the lead point distance, the more "smoothed" and circular the red _commanded path_ will be. For really large lead point distances, the red _commanded path_ is nearly circular.  
            [![enter image description here][4]][4]
    1. The above **linear position controllers** are all "dead-reckoning"-based, using wheel encoder ticks to measure distance by looking at _relative distance changes_ from a known starting location. Adding any _absolute position measurements_ would require an absolute position "truth source", such as off-board camera-based positioning systems such as a [Vicon motion capture system](https://www.vicon.com/hardware/cameras/) or [OptiTrack](https://optitrack.com/) system (used by [@Stuff Made Here](https://www.youtube.com/watch?v=xHWXZyfhQas)), acoustic-based positioning systems, GPS, etc., to obtain "truth data" of absolute position. This "truth data" could be used to tweak your robot's internal dead-reckoning position estimates slowly over time.


## Final (and philosophical) thoughts

Anyway, the way I see it, that's the idea. That's the type of approach I took on my quadcopter controller: [Quadrotor 2 - Physics-based Flight controller demo w/lead point navigation & Arduino interface to RC Tx](https://www.youtube.com/watch?v=H5kXzpPFdII&t=35s), and that controller would also work perfectly for a 2-wheeled Segway-like self-balancing robot, too, since the quadcopter is governed by the same principles as the self-balancing robot. Controls has many options and layers. Physics should be part of many if not most of them. 

I'll also mention that I believe the entire thing above could be done on almost *any* computational platform, from a single Arduino Nano (ATmega328 microcontroller), to a powerful desktop Linux laptop. It just requires the right amount of software skill, I think. Engineering is hard. Programming is complicated. But, if you know enough about both, you can do really complicated things on really weak processors like the ATmega328 (Arduino Uno, Nano, etc). I have done some really complicated things on those processors, and I still have a ton more I'd like to do and learn.


## References:

1. My answer: [Numerical derivation and integration in code for physics, mapping, robotics, gaming, dead-reckoning, and controls](https://stackoverflow.com/a/72162992/4561887)
1. My physics notes from college: [eRCaGuy_Engineering/Equation_Sheets/Physics 110 (General Physics I) - Constants and Equations - Staples#2.pdf](https://github.com/ElectricRCAircraftGuy/eRCaGuy_Engineering/blob/main/Equation_Sheets/Physics%20110%20(General%20Physics%20I)%20-%20Constants%20and%20Equations%20-%20Staples%232.pdf)
1. My quadcopter simulation: [1/3 - Autonomous quadcopter guidance and control (*physics-based* pure pursuit simulation)](https://www.youtube.com/watch?v=LjuPA43HceQ)
    1. See the notes under this video. I jotted down there that `a = F/m = g*tan(tilt_angle)`. That's how I was able to remember how to draw my "Balance of Forces" diagram above. 
1. My quadcopter live demo of my physics-based controller I described above: [3/3 - Autonomous quadcopter guidance & control (*physics-based* pure pursuit demonstration)](https://www.youtube.com/watch?v=H5kXzpPFdII&t=35s)
1. All 3 of my flight controller videos: https://github.com/ElectricRCAircraftGuy#flight-controller-videos
1. https://en.wikipedia.org/wiki/Equations_of_motion


## See also:
1. My answer: [Quadcopter PID Controller for distance](https://stackoverflow.com/a/73031923/4561887)
1. Potential vehicle I could buy to experiment with my full algorithm as I described it: [ELEGOO Tumbller Self-Balancing Robot Car Kit Compatible with Arduino, STEM Kits STEM Toys for Kids](https://amzn.to/3zdF00E). This would be a really fun project.
1. Google search for ["how to write an lqr controller"](https://www.google.com/search?q=how+to+write+an+lqr+controller&oq=how+to+write+an+lqr+controller&aqs=chrome..69i57.6257j0j7&sourceid=chrome&ie=UTF-8) (LQR = Linear Quadratic Regulator)
1. Google search for ["cascade control"](https://www.google.com/search?q=cascade+control&oq=cascade+control&aqs=chrome..69i57.3705j0j9&client=ms-android-google&sourceid=chrome-mobile&ie=UTF-8). This refers to the idea of "nested control loops", which is what my controller described above is/does.

<!--
Notes and feedback from a friend:

(To study and incorporate into the answer perhaps)

"command the 0 m/s velocity a little early". I called this Target Shaping at the satellite place. I've heard it in university as making a Motion Profile. If you already know reasonable limits of vehicle/robot acc and vel, you can create s-curve targets. Better to feed controllers with targets that can actually be achieved. Step changes in targets are just asking for a result that you didn't want.

-->



  [1]: https://i.stack.imgur.com/CMVcI.png
  [2]: https://i.stack.imgur.com/AeIts.jpg
  [3]: https://i.stack.imgur.com/WetMd.png
  [4]: https://i.stack.imgur.com/tJyj7.png
