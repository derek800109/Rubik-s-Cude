
<h4>The sample of output</h4>
12_0/0_1/5_2/3_3/4_4<br/>
222000022111111114525525125333333254044044300340355544

The meaning of this output is that:<br/>
1. (the way of rotation)_(th of the step)/<br/>
2. Every numbers have their correspondign color<br/>
enum NAMEOFCOLOR {RED = 0, YELLOW = 1, GREEN = 2, WHITE = 3, BLUE = 4, ORANGE = 5, TRANSPARENT = 6};<br/>
3. Every nine digit represent a face(A), and the sort of face is (B), which is mean from left up to right down<br/>

<h4>(A)The sort of faces</h4>
enum NAMEOFFACE {FRONT = 0, TOP = 1, RIGHT = 2, BUTTOM = 3, LEFT = 4, REAR = 5};
<h4>(B)The map of the cube:</h4>
<h5>The order of cells on each face</h5>
[U: upside, R: rightside, D: downside, L: leftside]
<table>
  <tr>
    <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>0</th><th>1(U)</th><th>2</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>3(L)</th><th>4</th><th>5(R)</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>6</th><th>7(D)</th><th>8</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>8</th><th>7(D)</th><th>6</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>5(R)</th><th>4</th><th>3(L)</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>2</th><th>1(U)</th><th>0</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>6</th><th>3(L)</th><th>0</th><th>&nbsp</th><th>0</th><th>1(U)</th><th>2</th><th>&nbsp</th><th>2</th><th>5(R)</th><th>8</th><th>&nbsp</th><th>8</th><th>7(D)</th><th>6</th>
  </tr>
      <th>7(D)</th><th>4</th><th>1(U)</th><th>&nbsp</th><th>3(L)</th><th>4</th><th>5(R)</th><th>&nbsp</th><th>1(U)</th><th>4</th><th>7(D)</th><th>&nbsp</th><th>5(R)</th><th>4</th><th>3(L)</th>
  </tr>
      <th>8</th><th>5(R)</th><th>2</th><th>&nbsp</th><th>6</th><th>7(D)</th><th>8</th><th>&nbsp</th><th>0</th><th>3(L)</th><th>6</th><th>&nbsp</th><th>2</th><th>1(U)</th><th>0</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>0</th><th>1(U)</th><th>2</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>3(L)</th><th>4</th><th>5(R)</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
      <th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>6</th><th>7(D)</th><th>8</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th><th>&nbsp</th>
  </tr>
</table>
<h5>The order of each face</h5>
<table>
  <tr>
    <th></th><th>RearFace</th><th></th><th></th>
  </tr>
  <tr>
    <th></th><th>UpFace</th><th></th><th></th>
  </tr>
  <tr>
    <th>LeftFace</th><th>FrontFace</th><th>RightFace</th><th>RearFace</th>
  </tr>
  <tr>
    <th></th><th>DownFace</th><th></th><th></th>
  </tr>
</table>
 
<h4>The way of rotation:</h4>

enum ROTATION3D {
    TOPCW = 0, TOPCCW = 1,
    BUTTOMCW = 2, BUTTOMCCW = 3,
    LEFTCW = 4, LEFTCCW = 5,
    RIGHTCW = 6, RIGHTCCW = 7,
    FRONTCW = 8, FRONTCCW = 9,
    REARCW = 10, REARCCW = 11,
    ORIGIN = 12
};
