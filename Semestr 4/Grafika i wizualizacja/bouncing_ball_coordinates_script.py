import numpy as np
import matplotlib.pyplot as plt

# Physics constants
g = 9.81  # Acceleration due to gravity

# Animation parameters
x_start = 8
x_end = -8
z_start = 6
z_ground = -3.4
num_bounces = 5
total_time = 10  # Total time for the animation
num_frames = 50  # Number of frames for the animation
restitution_coefficient = 0.8  # Adjust this value to make the ball more bouncy

# Generate time points
t_points = np.linspace(0, total_time, num_frames)

# Function to calculate the trajectory
def bounce_trajectory(t, x_start, x_end, z_start, z_ground, num_bounces, restitution_coefficient):
    x = np.linspace(x_start, x_end, len(t))
    z = np.zeros_like(t)
    t_bounce = total_time / num_bounces
    v0_z = np.sqrt(2 * g * (z_start - z_ground))  # Initial z-velocity for the first bounce
    
    for i in range(num_bounces):
        t0 = i * t_bounce
        t1 = (i + 1) * t_bounce
        mask = (t >= t0) & (t < t1)
        t_local = t[mask] - t0
        
        if i == 0:
            z[mask] = z_start - 0.5 * g * t_local**2  # First bounce from z_start
        else:
            # Calculate peak height for subsequent bounces
            v0_z *= restitution_coefficient  # Adjust the velocity for bounce
            z[mask] = z_ground + v0_z * t_local - 0.5 * g * t_local**2
        
        z[z < z_ground] = z_ground  # Ensure the ball doesn't go below the ground
    
    return x, z

# Calculate the trajectory
x, z = bounce_trajectory(t_points, x_start, x_end, z_start, z_ground, num_bounces, restitution_coefficient)

# Plotting the trajectory
plt.plot(x, z)
plt.xlabel('x')
plt.ylabel('z')
plt.title('Bouncing Ball Trajectory')
plt.grid(True)
plt.show()

# Print the coordinates rounded to 2 decimal places
coordinates = [(round(xi, 2), round(zi, 2)) for xi, zi in zip(x, z)]
print(coordinates)