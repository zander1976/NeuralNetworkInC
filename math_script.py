import numpy as np
import matplotlib.pyplot as plt

# Define the unit step function u(t - a)
def u(t, a):
    return np.heaviside(t - a, 1)  # Heaviside function represents u(t-a)

# Define the time variable
t = np.linspace(0, 6, 1000)  # Time from 0 to 6 with 1000 points

# Define the function x(t) using piecewise components
x = 2 * t - 2 * (t - 1) * u(t, 1) - 2 * (t - 3) * u(t, 3) + 2 * (t - 4) * u(t, 4)
x = t - (t-1) * u(t, 1)
#x = 2 * t - 2 * (t - 1) * u(t, 1) - 2 * (t - 3) * u(t, 3) + 2 * (t - 4) * u(t, 4)


# Plotting
plt.figure(figsize=(8, 4))
plt.plot(t, x, label='x(t)', color='blue', linewidth=2)
plt.title('Plot of x(t) = 2t - 2(t-1)u(t-1) - 2(t-3)u(t-3) + 2(t-4)u(t-4)')
plt.xlabel('Time (t)')
plt.ylabel('x(t)')
plt.grid(True)
plt.axvline(x=1, color='gray', linestyle='--', label='t=1')
plt.axvline(x=3, color='gray', linestyle='--', label='t=3')
plt.axvline(x=4, color='gray', linestyle='--', label='t=4')
plt.legend()
plt.ylim(-5, 10)
plt.xlim(0, 6)
plt.show()
