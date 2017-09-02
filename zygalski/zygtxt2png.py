from PIL import Image, ImageFont, ImageDraw
import sys

if  len(sys.argv)<2:
    print 'Need zygalski sheet in .txt as argument'
    quit();
else:
    filein = str(sys.argv[1])
    fileout = filein.replace('.txt','.png')
    sheetname=filein[-8:-4]

    
    


img = Image.new('RGBA',(1100, 1100),(255,255,255,0))
draw = ImageDraw.Draw(img)





draw.rectangle(((0,0),(1100,1100)), fill=(0,0,0,200))
for n in range (0,53):
    draw.rectangle(((57+n*20,57),(60+n*20,1100)), fill=(0,0,0,255))
    draw.rectangle(((57,57+n*20),(1100,60+n*20)), fill=(0,0,0,255))

    
font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 20)
draw.text((10,5), sheetname[0:3], font=font, fill=(255,255,255,128))

font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 40)
draw.text((18,20), sheetname[3], font=font, fill=(255,255,255,128))

font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 18)
draw.text((930,5), "Fast Rotor -->", font=font, fill=(255,255,255,128))

vert_text="Middle Rotor||v"
for n in range(0,15):
    draw.text((5,800+n*19), vert_text[n], font=font, fill=(255,255,255,128))





font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeMono.ttf", 25)
for n in range (0,26):
    draw.text((62+n*20, 26), chr(n+65), font=font, fill=(255,255,255,128))
    draw.text((582+n*20, 26), chr(n+65), font=font, fill=(255,255,255,128))
    draw.text((32, 56+n*20), chr(n+65), font=font, fill=(255,255,255,128))
    draw.text((32, 576+n*20), chr(n+65), font=font, fill=(255,255,255,128))


# open the text file and draw a transparent rectangle for a hole, in all 4 quadrants    
lc=0;
with open(filein, "r") as ins:
    for line in ins:
        for n in range(0,26):
            if (line[n]=='O'):
                draw.rectangle(((61+n*20,61+lc*20),(76+n*20,76+lc*20)), fill=(0,0,0,32))
                draw.rectangle(((26*20+61+n*20,61+lc*20),(26*20+76+n*20,76+lc*20)), fill=(0,0,0,32))
                draw.rectangle(((61+n*20,26*20+61+lc*20),(76+n*20,26*20+76+lc*20)), fill=(0,0,0,32))
                draw.rectangle(((26*20+61+n*20,26*20+61+lc*20),(26*20+76+n*20,26*20+76+lc*20)), fill=(0,0,0,32))
        lc=lc+1        
        



img.save(fileout, 'PNG')