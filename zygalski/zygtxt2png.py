from PIL import Image, ImageFont, ImageDraw

# Open zygalski file in txt format
# create a new image
# draw text to image
# draw "holes"
# save image to file.

img = Image.new('RGBA',(1100, 1100),(255,255,255,0))
draw = ImageDraw.Draw(img)

# use a bitmap font
#font = ImageFont.load("arial.pil")
#draw.text((10, 10), "hello", font=font)

# use a truetype font

draw.rectangle(((0,0),(1100,1100)), fill=(0,0,0,200))
for n in range (0,53):
    draw.rectangle(((57+n*20,57),(60+n*20,1100)), fill=(0,0,0,255))
    draw.rectangle(((57,57+n*20),(1100,60+n*20)), fill=(0,0,0,255))

font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 25)
for n in range (0,26):
    draw.text((62+n*20, 26), chr(n+65), font=font, fill=(255,255,255,128))
    draw.text((582+n*20, 26), chr(n+65), font=font, fill=(255,255,255,128))
    draw.text((32, 56+n*20), chr(n+65), font=font, fill=(255,255,255,128))
    draw.text((32, 576+n*20), chr(n+65), font=font, fill=(255,255,255,128))



#for c in range(0,25)
#    draw.text((25, 25), "world", font=font, fill=(255,255,255,128))
#draw.text((80, 80), "world", font=font, fill=(255,255,255,255))

img.save('test.png', 'PNG')