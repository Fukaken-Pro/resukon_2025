
import pygame
import time
import controller_get as con
pygame.init()
j = pygame.joystick.Joystick(0)
j.init()
print("コントローラのボタンを押してください")
print(j.get_id())
print(j.get_numaxes())
# print(con.getstick(0, 1, None, None, j))
# time.sleep(0.1)
# j.quit()
