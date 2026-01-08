import pandas as pd
import matplotlib.pyplot as plt

column_names = ["index", "reflex", "mean"]

ttv_data = pd.read_csv("iot-wokwi/touch-timer-visualization/data.csv",names=column_names)

fig, ax1 = plt.subplots()

color1 = "tab:blue"
ax1.set_xlabel("Index")
ax1.set_ylabel("Reflex", color=color1)
ax1.plot(ttv_data['index'], ttv_data['reflex'], marker='o', linestyle='-', color='blue')

ax2 = ax1.twinx()

color2 = "tab:red"
ax2.set_ylabel("Mean", color=color2)
ax2.plot(ttv_data['index'], ttv_data['mean'], marker='v', linestyle='-', color='red')
plt.title("Touch Timer Data Visualization")
plt.grid()
plt.show()