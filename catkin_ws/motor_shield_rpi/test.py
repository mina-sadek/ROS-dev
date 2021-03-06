from AMSpi import AMSpi
import time

# For BOARD pin numbering use AMSpi(True) otherwise BCM is used
with AMSpi() as amspi:
    # Set PINs for controlling shift register (GPIO numbering)
    amspi.set_74HC595_pins(21, 20, 16)
    # Set PINs for controlling all 4 motors (GPIO numbering)
    amspi.set_L293D_pins(PWM2A=13, PWM2B=19)
    # Run motors
    #amspi.run_dc_motors([amspi.DC_Motor_1])
    #amspi.run_dc_motors([amspi.DC_Motor_2])
    amspi.run_dc_motors([amspi.DC_Motor_1, amspi.DC_Motor_2])
    # amspi.run_dc_motors([amspi.DC_Motor_1, amspi.DC_Motor_2, amspi.DC_Motor_3, amspi.DC_Motor_3])
    time.sleep(100)
    amspi.stop_dc_motors([amspi.DC_Motor_1, amspi.DC_Motor_2])


