# Game Logic:
Entire set of kinematics could be thought of as a state vector which defines the state of a sprite at any given time step t.

### State Vector
This game will have two main sprintes, a set of mechazilla arms(just like the ones SpaceX have for catching the starship's booster). Each sprite will have a 

But before anything, let's have **Axis Reference**:
- X-axis is along the horizontal(right positive).
- Y-axis is along the vertial(upwards positive).
- Origin in calculations is the center of the screen.
- But ( $X,Y$ ) have to mapped on pixels:
  - Pixelwise origin(0,0) is top left of the screen.

Dynamics equations for each parameter(each parameter HAVE to be updated, write logic for each!)

$$
\text{State Vector} = [
                X, Y, V_x, V_y, A_x, A_y,\theta_R, \omega_R, \alpha_R, \theta_V
            ]\\
$$

Here:
- The point $(X,Y)$ will become the tip of the nose cone of the booster.
- $V_x,V_y$ will become the tip of the nose cone of the booster.
- $A_x, A_y$ will become the tip of the nose cone of the booster.
- $\theta_R$ will be the orientation of the rocket.
- $\omega_R$ will be the angular velocity of the rocket measured anticlockwise from the x axis.
- $\alpha$ will be the angular acceleration of the rocket produced by the torque from the vectorized thrust anti(clockwise positive).
- $\theta_V$ will be the orientation of the thrust vector w.r.t rocket's body.

There have to be some very important variables defined internally, namely:
- $g =$ Earth's gravitational acceleration
- $H =$ Height of the booster
- $H_s =$ Height of the screen
- $W_s =$ Width of the screen
- $M_R =$ Mass of the booster
- $I_R =$ Moment of Inertia
- $\vec{T} =$ Thrust vector:
    - A list of floats for each dt timestep.
    - It will eventually be replaced with 0.0 if ran out of non-zero values(meaning fuel is finished).
- $\theta_T$ = Absolute angle that the thrust makes with the x axis, measured anticlockwise.
  - $\theta_T = \theta_R-\theta_V$
- $\vec{\tau} =$ Torque


### Game constraints(for it to make some sense):
- Thrust profile has to be already fed in as per the landing, like should that be a soft descent throughout or a quick descent initially followed up with a lot of thrust at the last seconds.
- Touching the ground will result in an explosion.
- Touching the mechazilla with a velocity higher than a threshold velocity.
- There have to be an upper and a lower bound on the $\theta_v$. This is to simulate the real rocket because there's only so much control authority. You can't point the thrust vector anywhere you want!
- There have to be a minimum, discretized time step value. We are calling it dt, and we will keep it 0.1 seconds initially(as we have to manually enter in the thrust curve).

## Kinematics(motion equations):
- To simply things here we can assume a constant mass of the rocket/booster.
#### A. Translational Parameters:
- { $A_x, A_y$ } will be calculated from:
  - Predefined thrust values
  - $A_x = T*\sin{\theta_T} / M_R$
  - $A_y = T*\cos{\theta_T} / M_R$
- { $V_x, V_y$ } will be calculated using:
  - $V_x = V_x + A_x * dt$
  - $V_y = V_y + A_y * dt$
- { $X,Y$ } will be calculated using:
  - $X = X + V_x * dt$
  - $Y = Y + V_y * dt$

#### B. Rotational Parameters:
- Control Inputs will decide the value of $\theta_V$ which will then govern the 
  - $\alpha_R = {\tau} / {I}$
  - Torque ( $\vec{\tau}$ ) Calculations about booster's center of mass:
    ---------
    - $\vec{\tau} = \vec{r} \times \vec{F}$ 
        <br>Here $\vec{F}$ is nothing but the sine component of $\vec{T}$ at $\theta_T$
    - $\tau = (H/2) * T \sin{\theta_T}$
    - $\alpha_R = ( (H/2) * T \sin{\theta_T} ) / {I}$
- $\omega_R = \omega_R + \alpha_R * dt$
- $\theta_R = \theta_R + \alpha_R * dt$


  



### Scale – Meters to Pixels:
- All the parameters would be using meters, we will simply multiply them by F, a floating point value.
- It's value will be chosen as to what makes the most sense as per the sprite and the screen size & resolution.


Winning and loosing conditions will be checked at the end of every loop iteration of the indefinite while loop.

### Winning Condition checks:
- If $\omega$ is within a certain range.
- If $V_y$ is within a certain range.
- If $V_x$ is within a certain range.
- If the point $(X,Y)$ is within a certain range.

### Loosing Condition checks:
- If $\omega, V_x, V_y$ is not within those limits 
&& 
- (Y - H) came within



# Unit Tests:
- Test the kinematics equations with random thrust vector curve and plot graphs to see if the state vector makes sense.
    - Do it with only `x` and `y` coordinates with `V_x`, `V_y` first.

# Developlmental Milestones:
- Achieve a Vertical Landing with no control inputs, preferrentiably with sound effects.
