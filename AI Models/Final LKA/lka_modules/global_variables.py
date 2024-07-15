from lka_modules.pid import PIDController
import datetime
import paho.mqtt.client as mqtt

HORIZON = 69
BOTTOM_TRIM = 99
BOTTOM_MARGIN = 0
TOP_MARGIN = 23
camera_ip = "http://192.168.196.186:81/stream"

# PID Controller Constants
KP = 10  # Proportional. This is used to correct for the current error.
KI = 0  # Integral. This is used to correct for steady-state error.
KD = 2  # Derivative. This is used to dampen the oscillations around the setpoint.
INTEGRAL_LIMIT = 100  # Maximum value for the integral term. This is to prevent integral windup, which can cause the controller to overshoot.
DERIVATE_FILTER_TAU = 0.01  # Time constant for the derivative filter. This is used to smooth out the derivative term.
SETPOINT_WEIGHTS = (
    1,
    0.1,
)  # Weights for the setpoint and derivative term. This is used to prioritize the setpoint over the derivative term.


# Input can either be a video on disk, or a live video stream from a USB camera
# Video files are stored in the test_videos directory.
# See the very bottom of the script for the list of available videos.
VIDEO_OR_CAMERA = "camera"  # "video" or "camera"

# ROAD WIDTH
ROAD_WIDTH = 25  # centimeters

# Set to True to hide the region of interest overlay
HIDE_ROI = False

# Initialize buffers for storing line coefficients
left_line_buffer = []
right_line_buffer = []
angle_buffer = 90
buffer_length = 10  # Determines how many frames to average over


broker_address = "localhost"
port = 1883
# Create a MQTT client
client = mqtt.Client("esp/subtopic")
client.connect(broker_address, port)


pid_controller = PIDController(
    kp=KP,
    ki=KI,
    kd=KD,
    integral_limit=INTEGRAL_LIMIT,
    derivative_filter_tau=DERIVATE_FILTER_TAU,
    setpoint_weights=(SETPOINT_WEIGHTS),
)

previous_time = datetime.datetime.now()
