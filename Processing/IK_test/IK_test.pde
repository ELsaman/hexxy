float sx,sy,ex,ey,hx,hy,hxo,hyo;
int armLength,ua,la;
float uad, lad;
void setup(){
  size(800,800);
  background(255, 224, 150);
  sx = width/2;
  sy = height/2;
  armLength = int(width/5);
}
 
void draw(){
  fill(255);
  rect(0,0,width,height);
  upperArm();
}
 
void upperArm(){
  float fkt = int(500/50);
  
  
  float dx = max(mouseX, sx) - sx;
  float dy = max(-200, sy - mouseY);
  
  sx /= fkt;
  sy /= fkt;
  dx /= fkt;
  dy /= fkt;
  
  
  float a = 10; // coxa length
  float b = 12; // tibia length
  float h = 5; // hexapod base height
  float c = 0;
  float d = dx;
  
  float dh = abs(h - dy); // height delta
  c = min((a+b), sqrt(dh*dh + d*d));
  
  
  // above coxa -> B1 = 180 - B1
  float B1 = atan(d/dh);
  if (dy > h)
  {
    B1 = PI - B1;
  }
  
  float B = acos((a*a + c*c - b*b) / (2*a*c));
  float C = acos((b*b + a*a - c*c) / (2*b*a));
  
  println("Angles " + degrees(B+B1) + " Angle B1: " + degrees(B1) + " B: " + degrees(B));
  println("Angle C: " + degrees(C));
  
  
  // output / lines
  
  sx *= fkt;
  sy *= fkt;
  
  h *= fkt;
  a *= fkt;
  b *= fkt;
  dx *= fkt;
  dy *= fkt;
  
  float diam = 0.2*(a+b);
  ellipse(sx, sy - h, diam*fkt,diam*fkt);
  
  
  float femX = sx - a * cos(PI*2 - (B + B1 + PI/2));
  float femY = sy - h - a * sin(PI*2 - (B + B1 + PI/2));
  line(sx, sy - h, femX, femY);
  
  float tibX = femX - b * cos(PI*2 - (C + B + B1 - PI/2));
  float tibY = femY - b * sin(PI*2 - (C +B + B1 - PI/2));
  line(femX, femY, tibX, tibY);
  
  
  
  stroke(255,0,0,100);
  fill(240,0,0,200);
  ellipse(femX, femY, 10, 10);
  
  ellipse(sx, sy - h,10,10);
  line(sx - width / 2 ,sy - h,sx + width / 2,sy - h);
  stroke(0);
  line(sx - width / 2,sy,sx + width / 2,sy);
  line(sx,sy - height / 2,sx,sy + height / 2);
  fill(0,0,0,200);
  
  
  text("" + String.format("%.1f°", degrees(B+B1)), sx - 3*fkt, sy - h - 1.5*fkt );
  text("" + String.format("%.1f°", degrees(C)), femX + 1.5*fkt, femY - 1.5*fkt);
  
  text(""+dx+" | "+dy, tibX + 1.5*fkt, tibY + 1.5*fkt);
  
  ellipse(sx + dx, sy - dy, 10, 10);
  //for(int i = 1; i < diam / 2; i+=2)
  //{
    //text(""+i, sx + i * fkt, sy + 1.5* fkt);
    //text(""+i, sx - 1.5 * fkt, sy - i* fkt);
  //}
  
  
}