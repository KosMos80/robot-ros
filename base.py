import pygame, math

#colors
black = (0, 0, 0)

size = (500, 500)
screen = pygame.display.set_mode(size)

a = b = 200

clock = pygame.time.Clock()
FPS = 60

for i in range(1, 361, 3):
    clock.tick(FPS)
    angle = i * 3.14 / 180
    a = 100 * math.cos(angle) + 300
    b = 100 * math.sin(angle) + 300
    screen.fill(black)
    pygame.draw.polygon(screen, (255, 0, 255), [(int (a), int (b)),(int (a) - 20, int (b) + 10), (int (a) + 20, int (b) + 10)])
    pygame.display.update()