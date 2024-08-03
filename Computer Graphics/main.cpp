#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

 HWND hComboBox,colorComboBox,hDropdown,TDropdown;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int index = -1,p_index=-1, colorIndex,transformationIndex;
int clippingpolygon_num, convex_num, flood_num,ellipse_A,ellipse_B,quarter_num;
double translate_x,translate_y,scale_x,scale_y;
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
{
      //Try to make combination between your console and window */
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    //Filling Circle Quarter
    WriteConsoleA(hStdOut, "Filling Circle-> Enter quarter num: ", sizeof("Filling Circle-> Enter quarter num: ") - 1, &written, nullptr);
    cin >> quarter_num;
    //Convex
    WriteConsoleA(hStdOut,"Convex-> Enter num of shape's point: ",sizeof("Convex-> Enter num of shape's point: ") - 1,&written,nullptr);
    cin >> convex_num;
    //Flood Fill
    WriteConsoleA(hStdOut,"Flood Fill-> Enter num of shape's point: ",sizeof("Flood Fill-> Enter num of shape's point: ") - 1,&written,nullptr);
    cin >> flood_num;
    //Ellipse
    WriteConsoleA(hStdOut, "Ellipse-> Enter A,B: ", sizeof("Ellipse-> Enter A,B: ") - 1, &written, nullptr);
    cin >> ellipse_A>> ellipse_B;
    //Clipping Polygon
    WriteConsoleA(hStdOut,"Clipping-> Enter num of polygon's point: ",sizeof("Clipping-> Enter num of polygon's point: ") - 1,&written,nullptr);
    cin >> clippingpolygon_num;
    //Translate
    WriteConsoleA(hStdOut, "Translate-> Enter x,y: ", sizeof("Translate-> Enter x,y: ") - 1, &written, nullptr);
    cin >> translate_x>> translate_y;
    //Scale
    WriteConsoleA(hStdOut, "Scale-> Enter x,y: ", sizeof("Scale-> Enter x,y: ") - 1, &written, nullptr);
    cin >> scale_x>> scale_y;

    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    //WNDCLASSEX wincl;        /* Data structure for the windowclass */
    WNDCLASS wincl = {};        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    //wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    //wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    //wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */

    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    RegisterClass(&wincl);
    //if (!RegisterClassEx (&wincl))
      //return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

// Line*********************************************************************************************************
// Implement line algorithms [Parametric]
void swapElements(int& x,int& y)
{
    int tmp=x;
    x=y;
    y=tmp;
}
void drawLineParametric(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    if(abs(dy)<=abs(dx))
    {
        double slope=(double)dy/dx;
        if(xs>xe)
        {
            swapElements(xs,xe);
            swapElements(ys,ye);
        }
        for(int x=xs; x<=xe; x++)
        {
            int y=round(ys+(x-xs)*slope);
            SetPixel(hdc,x,y,color);
        }
    }
    else
    {
        double islope=(double)dx/dy;
        if(ys>ye)
        {
            swapElements(xs,xe);
            swapElements(ys,ye);
        }
        for(int y=ys; y<=ye; y++)
        {
            int x=round(xs+(y-ys)*islope);
            SetPixel(hdc,x,y,color);
        }
    }
}
//Implement line algorithms [DDA]
void drawLineSimpleDDA(HDC hdc,int xs,int ys,int xe,int ye,COLORREF color)
{
    int dx=xe-xs;
    int dy=ye-ys;
    SetPixel(hdc,xs,ys,color);
    if(abs(dx)>=abs(dy))
    {
        int x=xs,xinc;
        if(dx>0)
            xinc=1;
        else
            xinc=-1;
        double y=ys,yinc=(double)dy/dx*xinc;
        while(x!=xe)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,x,round(y),color);
        }
    }
    else
    {
        int y=ys,yinc;
        if(dy>0)
            yinc=1;
        else
            yinc=-1;
        double x=xs,xinc=(double)dx/dy*yinc;
        while(y!=ye)
        {
            x+=xinc;
            y+=yinc;
            SetPixel(hdc,round(x),y,color);
        }
    }
}
//Implement line algorithms [MidPoint]
void drawLineMidPoint(HDC hdc,int x1, int y1, int x2, int y2, COLORREF color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x = x1, y = y1;
    int step_x;
    if (x2>x1)
        step_x = 1;
    else
        step_x = -1;

    int step_y;
    if (y2>y1)
        step_y = 1;
    else
        step_y = -1;
    if (dx >= dy)
    {
        // Case 1: x is independent variable

        int D = dx - 2*dy;
        while (x != x2)
        {
            SetPixel(hdc,x, y,color);
            if (D < 0)
            {
                y += step_y;
                D += (2 * dx - 2 * dy);
            }
            else
                D -= 2 * dy;
            x += step_x;
        }
        SetPixel(hdc,x, y,color);
    }
    else
    {
        // Case 2: y is independent variable
        int D = dy - 2*dx;
        while (y != y2)
        {
            SetPixel(hdc,x, y,color);
            if (D < 0)
            {
                x += step_x;
                D += (2 * dy - 2 * dx);
            }
            else
                D -= 2 * dx;
            y += step_y;
        }
        SetPixel(hdc,x, y,color);
    }
}
// Circle********************************************************************************************************
//Implement Draw8Points Circle
void Draw8Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc+a, yc-b, color);
    SetPixel(hdc, xc+b, yc+a, color);
    SetPixel(hdc, xc-b, yc+a, color);
    SetPixel(hdc, xc-b, yc-a, color);
    SetPixel(hdc, xc+b, yc-a, color);
}
//Implement Circle algorithms (Direct)
void drawCircleDirect(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int R2=R*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        x++;
        y=round(sqrt((double)(R2-x*x)));
        Draw8Points(hdc,xc,yc,x,y,color);

    }
}
//Implement Circle algorithms (Polar)
void drawCirclePolar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=R,y=0;
    double theta=0,dtheta=1.0/R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x>y)
    {
        theta+=dtheta;
        x=round(R*cos(theta));
        y=round(R*sin(theta));
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}
//Implement Circle algorithms (Iterative Polar)
void drawCircleIterativePolar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    double x=R,y=0;
    double dtheta=1.0/R;
    double cdtheta=cos(dtheta),sdtheta=sin(dtheta);
    Draw8Points(hdc,xc,yc,R,0,color);
    while(x>y)
    {
        double x1=x*cdtheta-y*sdtheta;
        y=x*sdtheta+y*cdtheta;
        x=x1;
        Draw8Points(hdc,xc,yc,round(x),round(y),color);
    }
}
//Implement Circle algorithms (Midpoint)
void drawCircleMidpoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
            d+=2*x+3;
        else
        {
            d+=2*(x-y)+5;
            y--;
        }
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}
//Implement Circle algorithms (Modified Midpoint)
void drawCircleModifiedMidpoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}
// Filling Quarter***********************************************************************************************
//Filling Circle with lines after taking filling quarter from user
void fillingCircleWithLines(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=R,y=0;
    double theta=0,dtheta=1.0/R;
    Draw8Points(hdc,xc,yc,x,y,color);
    if(quarter_num==1)
    {
        drawLineSimpleDDA(hdc,xc,yc,xc+x,yc-y,color);drawLineSimpleDDA(hdc,xc,yc,xc+y,yc-x,color);
    }
    else if(quarter_num==2)
    {
        drawLineSimpleDDA(hdc,xc,yc,xc-x,yc-y,color);drawLineSimpleDDA(hdc,xc,yc,xc-y,yc-x,color);
    }
    else if(quarter_num==3)
    {
        drawLineSimpleDDA(hdc,xc,yc,xc-x,yc+y,color);drawLineSimpleDDA(hdc,xc,yc,xc-y,yc+x,color);
    }
    else if(quarter_num==4)
    {
        drawLineSimpleDDA(hdc,xc,yc,xc+x,yc+y,color);drawLineSimpleDDA(hdc,xc,yc,xc+y,yc+x,color);
    }
    while(x>y)
    {
        theta+=dtheta;
        x=round(R*cos(theta));
        y=round(R*sin(theta));
        Draw8Points(hdc,xc,yc,x,y,color);
        if(quarter_num==1)
        {
            drawLineSimpleDDA(hdc,xc,yc,xc+x,yc-y,color);drawLineSimpleDDA(hdc,xc,yc,xc+y,yc-x,color);
        }
        else if(quarter_num==2)
        {
            drawLineSimpleDDA(hdc,xc,yc,xc-x,yc-y,color);drawLineSimpleDDA(hdc,xc,yc,xc-y,yc-x,color);
        }
        else if(quarter_num==3)
        {
            drawLineSimpleDDA(hdc,xc,yc,xc-x,yc+y,color);drawLineSimpleDDA(hdc,xc,yc,xc-y,yc+x,color);
        }
        else if(quarter_num==4)
        {
            drawLineSimpleDDA(hdc,xc,yc,xc+x,yc+y,color);drawLineSimpleDDA(hdc,xc,yc,xc+y,yc+x,color);
        }
    }
}
//Filling Circle with circles after taking filling quarter from user
void draw2Points(HDC hdc,int x, int y,int a,int b, COLORREF c)
{
    if(quarter_num==1)
    {
        SetPixel(hdc,x+a,y-b,c);
        SetPixel(hdc,x+b,y-a,c);
    }
    else if(quarter_num==2)
    {
        SetPixel(hdc,x-a,y-b,c);
        SetPixel(hdc,x-b,y-a,c);
    }
    else if(quarter_num==3)
    {
        SetPixel(hdc,x-a,y+b,c);
        SetPixel(hdc,x-b,y+a,c);
    }
    else if(quarter_num==4)
    {
        SetPixel(hdc,x+a,y+b,c);
        SetPixel(hdc,x+b,y+a,c);
    }

}
void drawcircule2Points(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    int x=0,y=r;
    int r2=r*r;
    draw2Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        x++;
        y=round(sqrt((double)(r2-x*x)));
        draw2Points(hdc,xc,yc,x,y,c);
    }
}
void fillingCircleWithCircles(HDC hdc,int xc,int yc,int r,COLORREF c)
{
    int x=0,y=r;
    int r2=r*r;
    int R=r;
    Draw8Points(hdc,xc,yc,x,y,c);
    while(x<y)
    {
        x++;
        y=round(sqrt((double)(r2-x*x)));
        Draw8Points(hdc,xc,yc,x,y,c);
    }
    while(R!=0)
    {
        R--;
        drawcircule2Points( hdc, xc, yc, R, c);
    }
}
// Filling Square***********************************************************************************************
//Filling Square with Hermit Curve[Vertical]
bool isPointInsideSquare(int x, int y, int xc, int yc, int l)
{
    return (x > xc - l+1 && x < xc + l-1 && y > yc - l+1 && y < yc + l-1);
}
void HermiteCurve(HDC hdc,double xc, double yc, double L, double x1, double y1, double u1, double v1, double x2, double y2, double u2, double v2, COLORREF col)
{
    double A0 = x1;
    double B0 = y1;
    double A1 = u1;
    double B1 = v1;
    double A2 = -3*x1 - 2*u1 + 3*x2 - u2;
    double B2 = -3*y1 - 2*v1 + 3*y2 - v2;
    double A3 = 2*x1 + u1 -2*x2 + u2;
    double B3 = 2*y1 + v1 -2*y2 + v2;
    for (double t=0 ; t<=1 ; t+= 0.0001){
        double x = A3*pow(t,3) + A2*pow(t,2) + A1*t + A0;
        double y = B3*pow(t,3) + B2*pow(t,2) + B1*t + B0;
        if(isPointInsideSquare(x,y,xc, yc, L)){SetPixel(hdc, x,y,RGB(0,255,0));}
    }
}
void fillingSquareHermitCurveVertical(HDC hdc, double xc, double yc, double L, COLORREF col)
{
    double
    x1 = xc, y1 = yc - L,
    u1 = x1 + L, v1 = y1,
    x2 = xc, y2 = yc + L,
    u2 = x2 - L, v2 = y2;
    while(x1<=xc+L+L){
        HermiteCurve(hdc,xc,yc,L, x1, y1, u1, v1, x2, y2, u2, v2, col);
        x1+=0.7, y1 ,u1+=0.7, v1, x2+=0.7 ,y2, u2+=0.7 ,v2;
    }
    x1 = xc;y1 = yc - L;u1 = x1 + L;v1 = y1;x2 = xc;y2 = yc + L;u2 = x2 - L;v2 = y2;
    while(x1>=xc-L-L){
        HermiteCurve(hdc,xc,yc,L, x1, y1, u1, v1, x2, y2, u2, v2, col);
        x1-=0.7, y1 ,u1-=0.7, v1, x2-=0.7 ,y2, u2-=0.7 ,v2;
    }
}
// Filling Rectangle***********************************************************************************************
//Filling Rectangle with Bezier Curve[horizontal]
bool isPointInsideRec(int x, int y, int xc, int yc, int W,int Len)
{
    return (x >= xc - W+1 && x <= xc + W-2 && y >= yc - Len+1 && y <= yc + Len-2);
}
void BerzierCurve(HDC hdc,double xc, double yc, double W,double Len, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, COLORREF col)
{
    double A0 = x1;
    double B0 = y1;
    double A1 = 3*(x2-x1);
    double B1 = 3*(y2-y1);
    double A2 = 3*x1 -6*x2+3*x3;
    double B2 = 3*y1 -6*y2+3*x3;
    double A3 = x4-x1+3*x2-3*x3;
    double B3 = y4-y1+3*y2-3*y3;
    for (double t=0 ; t<=1 ; t+= 0.0001){
        double x = A3*pow(t,3) + A2*pow(t,2) + A1*t + A0;
        double y = B3*pow(t,3) + B2*pow(t,2) + B1*t + B0;
        if(isPointInsideRec(x,y,xc, yc, W,Len)){SetPixel(hdc, x,y,RGB(0,255,0));}
    }
}
void drawBezierInRec(HDC hdc, double xc, double yc, double W,double Len, COLORREF col)
{
    double x1 = xc - W;
    double y1 = yc;
    double x2 = xc - W/2;
    double y2 = yc - W/2;
    double x3 = xc + W/2;
    double y3 = yc + W/2;
    double x4 = xc + W;
    double y4 = yc;
    BerzierCurve(hdc, xc, yc, W,Len, x1, y1, x2, y2, x3, y3, x4, y4, col);
    while(y1>=yc-W-W){
        BerzierCurve(hdc, xc, yc, W,Len ,x1, y1, x2, y2, x3, y3, x4, y4, col);
        y1--,y2--,y3++,y4++;
    }
    x1 = xc - W; y1=yc; x2 = xc - W/2; y2 = yc - W/2; x3 = xc + W/2; y3 = yc + W/2;x4 = xc + W;y4 = yc;
    while(y1<=yc+W+W){
        BerzierCurve(hdc, xc, yc, W,Len, x1, y1, x2, y2, x3, y3, x4, y4, col);
        y1+=0.5,y2+=0.5,y3-=0.5,y4-=0.5;
    }

}
// Convex********************************************************************************************************
//Convex Filling Algorithm
const int CMAXENTRIES =600;
struct Entry {int xmin,xmax;};
void InitEntries(Entry table[])
{
    for(int i=0 ; i<CMAXENTRIES ; i++){
        table[i].xmin=INT_MAX;
        table[i].xmax=-INT_MAX;
    }
}
void ScanEdge(POINT v1,POINT v2,Entry table[])
{
    if(v1.y==v2.y)return;
    if(v1.y>v2.y) std::swap(v1,v2);
    double minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    double x=v1.x;
    int y=v1.y;
    while(y<v2.y)
    {
        if(x<table[y].xmin){ table[y].xmin=(int)ceil(x); } //xleft  ceil to keep xleft inside polygon
        if(x>table[y].xmax){ table[y].xmax=(int)floor(x); } //xright floor to keep xright inside polygon
        y++;
        x+=minv;
    }
}
void DrawSanLines(HDC hdc,Entry table[],COLORREF color)
{
    for(int y=0;y<CMAXENTRIES;y++){
        if(table[y].xmin<table[y].xmax){
             for(int x=table[y].xmin;x<=table[y].xmax;x++){
                SetPixel(hdc,x,y,color);   ///draw horizontal line
             }
        }
    }
}
void ConvexFill(HDC hdc,POINT p[],int n,COLORREF color)
{
    Entry *table=new Entry[CMAXENTRIES];
    InitEntries(table);
    POINT v1=p[n-1];
    for(int i=0;i<n;i++){
        POINT v2=p[i];
        ScanEdge(v1,v2,table);
        v1=p[i];
    }
    DrawSanLines(hdc,table,color);
    delete table;
}
//Non Convex Filling Algorithm
const int NCMAXENTRIES =600;
struct EdgeRec
{
    double x;
    double minv;
    int ymax;
    bool operator<(EdgeRec r) {return x<r.x;}
};
typedef list<EdgeRec> EdgeList; /// one list of nodes called EdgeList
EdgeRec InitEdgeRec(POINT& v1,POINT& v2)    ///initialize node
{
    if(v1.y>v2.y)swap(v1,v2);
    EdgeRec rec;
    rec.x=v1.x;
    rec.ymax=v2.y;
    rec.minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
    return rec;
}
void InitEdgeTable(POINT polygon[],int n,EdgeList table[])  ///initialize the whole table
{
    POINT v1=polygon[n-1];
    for(int i=0;i<n;i++)
    {
        POINT v2=polygon[i];
        if(v1.y==v2.y){v1=v2;continue;}
        EdgeRec rec=InitEdgeRec(v1, v2);
        table[v1.y].push_back(rec);
        v1=polygon[i];
    }
}
void GeneralPolygonFill(HDC hdc,POINT polygon[],int n,COLORREF c)
{
    EdgeList *table=new EdgeList [NCMAXENTRIES]; ///array of EdgeList (each idx is a list of nodes)
    InitEdgeTable(polygon,n,table);
    int y=0;
    while(y<NCMAXENTRIES && table[y].size()==0){y++;} ///finding non empty index
    if(y==NCMAXENTRIES) return;
    EdgeList ActiveList=table[y];  ///assign 1st non empty record to ActiveList (ActiveList is a list of nodes)
    while (ActiveList.size()>0)
    {
        ActiveList.sort(); ///sort
        for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
        {
            int x1=(int)ceil(it->x);
            it++;
            int x2=(int)floor(it->x);
            for(int x=x1;x<=x2;x++)SetPixel(hdc,x,y,c);
        }
        y++;
        ///remove nodes with y = ymax
        EdgeList::iterator it=ActiveList.begin();
        while(it!=ActiveList.end())
            if(y==it->ymax) it=ActiveList.erase(it); else it++;
        ///update x values
        for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
            it->x+=it->minv;
        /// append t[y] to active , what if t[y] is empty idx in table ????????????????????????????????????????
        ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
    }
    delete[] table;
}
// Flood Fill******************************************************************************************************
//Recursive Flood Fill
void RecursiveFloodFill(HDC hdc,int x,int y,COLORREF Cb,COLORREF Cf)
{
    COLORREF C=GetPixel(hdc,x,y);
    if(C==Cb || C==Cf)return;
    SetPixel(hdc,x,y,Cf);
    RecursiveFloodFill(hdc,x+1,y,Cb,Cf);
    RecursiveFloodFill(hdc,x-1,y,Cb,Cf);
    RecursiveFloodFill(hdc,x,y+1,Cb,Cf);
    RecursiveFloodFill(hdc,x,y-1,Cb,Cf);
}
//Non Recursive Flood Fill
struct Point
{
    int x,y;
    Point(int x,int y):x(x),y(y) {}
};
void NonRecursiveFloodFill(HDC hdc,int x,int y,COLORREF Cb,COLORREF Cf)
{
    stack<Point> S;
    S.push(Point(x,y));
    while(!S.empty())
    {
        Point p=S.top();
        S.pop();
        COLORREF c=GetPixel(hdc,p.x,p.y);
        if(c==Cb || c==Cf)continue;
        SetPixel(hdc,p.x,p.y,Cf);
        S.push(Point(p.x+1,p.y));
        S.push(Point(p.x-1,p.y));
        S.push(Point(p.x,p.y+1));
        S.push(Point(p.x,p.y-1));
    }
}
void DrawShape(HDC hdc,POINT points[],int num,COLORREF color)
{
    for(int i=0;i<num-1;i++)
        {
            drawLineParametric(hdc,points[i].x,points[i].y,points[i+1].x,points[i+1].y,color);
        }
        drawLineParametric(hdc,points[0].x,points[0].y,points[num-1].x,points[num-1].y,color);
}
//Cardinal Spline Curve********************************************************************************************
struct Vector2
{
    double x,y;
    Vector2(double a=0,double b=0)
    {
        x=a;
        y=b;
    }
};
class Vector4
{
    double v[4];
public:
    Vector4(double a=0,double b=0,double c=0,double d=0)
    {
        v[0]=a;
        v[1]=b;
        v[2]=c;
        v[3]=d;
    }
    Vector4(double a[])
    {
        memcpy(v,a,4*sizeof(double));
    }
    double& operator[](int i)
    {
        return v[i];
    }
};
class Matrix4
{
    Vector4 M[4];
public:
    Matrix4(double A[])
    {
        memcpy(M,A,16*sizeof(double));
    }
    Vector4& operator[](int i)
    {
        return M[i];
    }
};
Vector4 operator*(Matrix4 M,Vector4& b)
{
    Vector4 res;
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            res[i]+=M[i][j]*b[j];
    return res;
}
double DotProduct(Vector4& a,Vector4& b)
{
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3];
}
Vector4 GetHermiteCoeff(double x0,double s0,double x1,double s1)
{
    static double H[16]= {2,1,-2,1,-3,-2,3,-1,0,1,0,0,1,0,0,0};
    static Matrix4 basis(H);
    Vector4 v(x0,s0,x1,s1);
    return basis*v;
}
void DrawHermiteCurve (HDC hdc,Vector2& P0,Vector2& T0,Vector2& P1,Vector2& T1,int numpoints)
{
    Vector4 xcoeff=GetHermiteCoeff(P0.x,T0.x,P1.x,T1.x);
    Vector4 ycoeff=GetHermiteCoeff(P0.y,T0.y,P1.y,T1.y);
    if(numpoints<2)return;
    double dt=0.0001;
    for(double t=0; t<=1; t+=dt)
    {
        Vector4 vt;
        vt[3]=1;
        for(int i=2; i>=0; i--)vt[i]=vt[i+1]*t;
        int x=round(DotProduct(xcoeff,vt));
        int y=round(DotProduct(ycoeff,vt));
        if(t==0)MoveToEx(hdc,x,y,NULL);
        else LineTo(hdc,x,y);
    }
}
void DrawCardinalSpline(HDC hdc,Vector2 P[],int n,double c,int numpix)
{
    double c1=1-c;
    Vector2 T0(c1*(P[2].x-P[0].x),c1*(P[2].y-P[0].y));
    for(int i=2; i<n-1; i++)
    {
        Vector2 T1(c1*(P[i+1].x-P[i-1].x),c1*(P[i+1].y-P[i-1].y));
        DrawHermiteCurve(hdc,P[i-1],T0,P[i],T1,numpix);
        T0=T1;
    }
}
//Ellipse**********************************************************************************************************
void Draw4Points(HDC hdc,int xc,int yc, int a, int b,COLORREF color)
{
    SetPixel(hdc, xc+a, yc+b, color);
    SetPixel(hdc, xc-a, yc-b, color);
    SetPixel(hdc, xc-a, yc+b, color);
    SetPixel(hdc, xc+a, yc-b, color);
}
//Ellipse Algorithms [Direct]
void EllipseDirect(HDC hdc,int xc,int yc, int A,int B,COLORREF color)
{
    double x=0,y=B;
    double A2=A*A;
    double B2=B*B;
    Draw4Points(hdc,xc,yc,x,y,color);
    while(x<A)
    {
        x+=0.01;
        y = round(sqrt(B2*(1-((x*x)/A2))));
        Draw4Points(hdc,xc,yc,x,y,color);
    }
}
//Ellipse Algorithms [Polar]
void EllipsePolar(HDC hdc,int xc,int yc, int A,int B,COLORREF color)
{
    int x=A,y=0;
    double theta=0,dtheta=1.0/A;
    Draw4Points(hdc,xc,yc,x,y,color);
    while(x>(y-B))
    {
        theta+=dtheta;
        x=round(A*cos(theta));
        y=round(B*sin(theta));
        Draw4Points(hdc,xc,yc,x,y,color);
    }
}
//Ellipse Algorithms [Midpoint]
void EllipseMidPoint(HDC hdc,int xc,int yc, int A, int B,COLORREF color)
{
    double x=0,y=B;
    int A2 = A*A;
    int B2 = B*B;
    double d = ((double)(0.01)/A2) - (1.0/B) + ((double)(1.0/4)/B2);
    Draw4Points(hdc,xc,yc,x,y,color);
    while(x<A)
    {
        if(d<0)
            d += ((double)(0.2*x+0.03)/A2);
        else
        {
            d += ((double)((double)(0.2*x+0.03)/A2) + ((double)(-2*y+2)/B2));
            y--;
        }
        x+=0.1;
        Draw4Points(hdc,xc,yc,x,y,color);
    }
}
// Clipping********************************************************************************************************
//Clipping algorithms [Point]
void PointClipping(HDC hdc,int x,int y,int xleft,int ytop,int xright,int ybottom,COLORREF color)
{
    if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
        SetPixel(hdc,x,y,color);
}
//Clipping algorithms [Line]
union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};
OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)out.left=1;
    else if(x>xright)out.right=1;
    if(y<ytop)out.top=1;
    else if(y>ybottom)out.bottom=1;
    return out;
}
void VIntersect(double xs,double ys,double xe,double ye,int x,double *xi,double *yi)
{
    *xi=x;
    *yi=ys+(x-xs)*(ye-ys)/(xe-xs);
}
void HIntersect(double xs,double ys,double xe,double ye,int y,double *xi,double *yi)
{
    *yi=y;
    *xi=xs+(y-ys)*(xe-xs)/(ye-ys);
}
void LineClipping(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom)
{
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        MoveToEx(hdc,round(x1),round(y1),NULL);
        LineTo(hdc,round(x2),round(y2));
    }
}
//Clipping algorithms [Polygon]
struct Vertex
{
    double x,y;
    Vertex(int x1=0,int y1=0)
    {
        x=x1;
        y=y1;
    }
};
typedef vector<Vertex> VertexList;
typedef bool (*IsInFunc)(Vertex& v,int edge);
typedef Vertex (*IntersectFunc)(Vertex& v1,Vertex& v2,int edge);
VertexList ClipWithEdge(VertexList p,int edge,IsInFunc In,IntersectFunc Intersect)
{
    VertexList OutList;
    Vertex v1=p[p.size()-1];
    bool v1_in=In(v1,edge);
    for(int i=0; i<(int)p.size(); i++)
    {
        Vertex v2=p[i];
        bool v2_in=In(v2,edge);
        if(!v1_in && v2_in)
        {
            OutList.push_back(Intersect(v1,v2,edge));
            OutList.push_back(v2);
        }
        else if(v1_in && v2_in) OutList.push_back(v2);
        else if(v1_in) OutList.push_back(Intersect(v1,v2,edge));
        v1=v2;
        v1_in=v2_in;
    }
    return OutList;
}
bool InLeft(Vertex& v,int edge)
{
    return v.x>=edge;
}
bool InRight(Vertex& v,int edge)
{
    return v.x<=edge;
}
bool InTop(Vertex& v,int edge)
{
    return v.y>=edge;
}
bool InBottom(Vertex& v,int edge)
{
    return v.y<=edge;
}
Vertex VIntersect(Vertex& v1,Vertex& v2,int xedge)
{
    Vertex res;
    res.x=xedge;
    res.y=v1.y+(xedge-v1.x)*(v2.y-v1.y)/(v2.x-v1.x);
    return res;
}
Vertex HIntersect(Vertex& v1,Vertex& v2,int yedge)
{
    Vertex res;
    res.y=yedge;
    res.x=v1.x+(yedge-v1.y)*(v2.x-v1.x)/(v2.y-v1.y);
    return res;
}
void PolygonClip(HDC hdc,POINT *p,int n,int xleft,int ytop,int xright,int ybottom)
{
    VertexList vlist;
    for(int i=0; i<n; i++)vlist.push_back(Vertex(p[i].x,p[i].y));
    vlist=ClipWithEdge(vlist,xleft,InLeft,VIntersect);
    vlist=ClipWithEdge(vlist,ytop,InTop,HIntersect);
    vlist=ClipWithEdge(vlist,xright,InRight,VIntersect);
    vlist=ClipWithEdge(vlist,ybottom,InBottom,HIntersect);
    Vertex v1=vlist[vlist.size()-1];
    for(int i=0; i<(int)vlist.size(); i++)
    {
        Vertex v2=vlist[i];
        MoveToEx(hdc,round(v1.x),round(v1.y),NULL);
        LineTo(hdc,round(v2.x),round(v2.y));
        v1=v2;
    }
}
//2D Transformation********************************************************************************************************
class transformationVector
{
    double v[3];
public:
    transformationVector()
    {
        v[0]=v[1];
        v[2]=1;
    }
    transformationVector(double x, double y)
    {
        v[0]=x;
        v[1]=y;
        v[2]=1;
    }
    void setValue(double x, double y)
    {
        v[0]=x;
        v[1]=y;
        v[2]=1;
    }
    double& operator[](int n)
    {
        return v[n];
    }
};
class Matrix2
{
    transformationVector A[3];
public:
    transformationVector& operator[](int n)
    {
        return A[n];
    }
    friend Matrix2 operator*(Matrix2& A,Matrix2& B)
    {
        Matrix2 C;
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
            {
                C[i][j]=0;
                for(int k=0; k<3; k++)C[i][j]+=A[i][k]*B[k][j];
            }
        return C;
    }
    friend transformationVector operator*(Matrix2& A,transformationVector& v)
    {
        transformationVector r;
        for(int i=0; i<3; i++)
        {
            r[i]=0;
            for(int j=0; j<3; j++)r[i]+=A[i][j]*v[j];
        }
        return r;
    }
    Matrix2& operator*=(Matrix2& B)
    {
        *this=*this*B;
        return *this;
    }
};
Matrix2 Identity()
{
    Matrix2 A;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            A[i][j]= i==j ;
    return A;
}
Matrix2 translate(double dx, double dy)
{
    Matrix2 T=Identity();
    T[0][2]=dx;
    T[1][2]=dy;
    return T;
}
Matrix2 scale(double alpha, double beta)
{
    Matrix2 Sc=Identity();
    Sc[0][0]=alpha;
    Sc[1][1]=beta;
    return Sc;
}
//Clear File********************************************************************************************************
void clearFile(const std::string& filename)
{
    std::ofstream ofs(filename, std::ios::trunc);
}
int checkColor(COLORREF color)
{
    if(color==RGB(255, 15, 20)) //Red
        return -1;
    else if(color==RGB(0, 0, 255)) //Blue
        return -2;
    else if(color==RGB(50, 0, 20)) //Brown
        return -3;
    else if(color==RGB(0, 0, 0)) //Black
        return -4;
    else if(color==RGB(112, 73, 179)) //Purple
        return -5;
    return 0;
}
COLORREF checkNumOfColor(int n)
{
    COLORREF tempColor;
    if(n==-1) //Red
        tempColor = RGB(255, 15, 20);
    else if(n==-2) //Blue
        tempColor = RGB(0, 0, 255);
    else if(n==-3) //Brown
        tempColor = RGB(50, 0, 20);
    else if(n==-4) //Black
        tempColor = RGB(0, 0, 0);
    else if(n==-5) //Purple
        tempColor = RGB(112, 73, 179);
    return tempColor;
}

// Variables
int line_xs,line_ys,line_xe,line_ye,line_count=0; //Line
int circle_xs,circle_ys,circle_xe,circle_ye,circle_r,circle_count=0; //Circle
int filling_xs,filling_ys,filling_xe,filling_ye,filling_r,filling_count=0; //Filling
int fillingsquare_xc=160,fillingsquare_yc=113,L=30; //Filling Square
int fillingrectangle_xc=98,fillingrectangle_yc=100,halfW=30,halfL=15; //Filling Rectangle
int convex_cnt=0; POINT *convex_P = new POINT[convex_num]; //Convex
int nonconvex_cnt=0; POINT *nonconvex_P = new POINT[convex_num]; //Non Convex
int flood_cnt=0,flood_count=0,flood_x,flood_y; POINT *flood_P = new POINT[flood_num]; //Flood Fill
Vector2 *spline_v= new Vector2[4]; int spline_cnt=0; //Cardinal Spline Curve
int ellipse_xc,ellipse_yc; //Ellipse
int x_left,y_top,x_right,y_bottom; //Clipping
int clippingpoint_xs,clippingpoint_ys,clippingpoint_count=0,clippingpoint1_count=0; //Clipping Point
int clippingline_xs,clippingline_ys,clippingline_xe,clippingline_ye,clippingline_count=0,clippingline1_count=0; //Clipping Line
int clippingpolygon_cnt=0,clippingpolygon_count=0; POINT *clippingpolygon_P = new POINT[clippingpolygon_num]; //Clipping Polygon
transformationVector startLine; transformationVector endLine;
Matrix2 identity; transformationVector formedStart; transformationVector formedEnd;
Matrix2 translationMatrix;transformationVector transformedStart;transformationVector transformedEnd;
Matrix2 scaleMatrix;transformationVector scaleformedStart;transformationVector scaleformedEnd;
int trans_xs,trans_ys,trans_xe,trans_ye; //Last Line
fstream MyFile;vector<int> vec,VEC;string c,v,x="",s;int count_vec=0;//File
RECT clientRect; HBRUSH hBrush; //Clear Screen
HCURSOR hCursorArrow = LoadCursor(NULL, IDC_ARROW);
HCURSOR hCursorHand = LoadCursor(NULL, IDC_HAND);
HCURSOR hCursorCrosshair = LoadCursor(NULL, IDC_CROSS);
HCURSOR hCursorD=hCursorArrow;

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);
    static COLORREF color; COLORREF CScreen;
    static int nLastSelectedIndex = 0;
    COLORREF tempColor;
    COLORREF fillingCol = RGB(0, 255, 0);
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE: //drop down list
        {
            hComboBox = CreateWindow("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,10, 10, 500, 600, hwnd, NULL, NULL, NULL);
            // Add items to the drop down list
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Select option...");//0
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Change the background of window to be white");//1
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Change the shape of your window mouse");//2
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Choose shape color");//3
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Clear screen");//4
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Save all data in screen");//5
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"load data from files");//6
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"line drawing DDA algorithm");//7
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"line drawing MidPoint algorithm");//8
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"line drawing parametric algorithm");//9
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Circle drawing Direct algorithm");//10
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Circle drawing Polar algorithm");//11
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Circle drawing iterative Polar algorithm");//12
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Circle drawing Midpoint algorithm");//13
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Circle drawing modified Midpoint algorithm");//14
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Filling Circle with lines after taking filling quarter from user");//15
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Filling Circle with other circles after taking filling quarter from user");//16
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Filling Square with Hermit Curve[Vertical]");//17
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Filling Rectangle with Bezier Curve[horizontal]");//18
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Convex Filling Algorithm");//19
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Non Convex Filling Algorithm");//20
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Recursive Flood Fill");//21
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Non Recursive Flood Fill");//22
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Cardinal Spline Curve");//23
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Ellipse drawing Direct");//24
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Ellipse drawing Polar");//25
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Ellipse drawing Midpoint]");//26
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Clipping algorithms using Rectangle as Clipping Window Point");//27
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Clipping algorithms using Rectangle as Clipping Window Line");//28
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Clipping algorithms using Rectangle as Clipping Window Polygon");//29
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Clipping algorithms using Square as Clipping Window Point");//30
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"Clipping algorithms using Square as Clipping Window Line");//31
            SendMessage(hComboBox, CB_ADDSTRING, 0, (LPARAM)"2D transformation");//32
            SendMessage(hComboBox, CB_SETCURSEL, 0, 0);
            SetCursor(hCursorD);
            break;
        }
    case WM_COMMAND:
        {
            if (lParam == (LPARAM)hComboBox && HIWORD(wParam) == CBN_SELCHANGE)
            {
                p_index=index;
                if(p_index==27)
                {
                    if(clippingpoint_count==1)
                        vec.push_back(-27);
                    clippingpoint_count=0;
                }
                if(p_index==30)
                {
                    if(clippingpoint1_count==1)
                        vec.push_back(-30);
                    clippingpoint1_count=0;
                }
                if(p_index==28)
                {
                    if(clippingline_count==1)
                        vec.push_back(-28);
                    clippingline_count=0;
                }
                if(p_index==31)
                {
                    if(clippingline1_count==1)
                        vec.push_back(-31);
                    clippingline1_count=0;
                }
                if(p_index==29)
                {
                    if(clippingpolygon_count==1)
                        vec.push_back(-29);
                    clippingpolygon_count=0;
                }
                SetCursor(hCursorD);
                index = SendMessage(hComboBox,CB_GETCURSEL,0,0);
                cout<<"index = "<<index<<endl;
                cout<<"P = "<<p_index<<endl;
                if(index==1) //Change the background of window to be white
                {
                    SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, reinterpret_cast<LONG_PTR>(CreateSolidBrush(RGB(255, 255, 255))));
                    InvalidateRect(hwnd, NULL, TRUE); // Redraw the window
                }
                else if(index==2) //chose mouse
                {
                    hDropdown = CreateWindow("COMBOBOX", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,150, 40, 100, 150, hwnd, reinterpret_cast<HMENU>(1), NULL, NULL);
                    SendMessage(hDropdown, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Arrow"));
                    SendMessage(hDropdown, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Hand"));
                    SendMessage(hDropdown, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Crosshair"));
                }
                else if(index==3) //color mouse
                {
                    colorComboBox = CreateWindow("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST,40, 40, 100, 150, hwnd, NULL, NULL, NULL);
                    SendMessage(colorComboBox, CB_ADDSTRING, 0, (LPARAM)"Red");
                    SendMessage(colorComboBox, CB_ADDSTRING, 0, (LPARAM)"Blue");
                    SendMessage(colorComboBox, CB_ADDSTRING, 0, (LPARAM)"Brown");
                    SendMessage(colorComboBox, CB_ADDSTRING, 0, (LPARAM)"Black");
                    SendMessage(colorComboBox, CB_ADDSTRING, 0, (LPARAM)"Purple");
                }
                else if(index==32) //transformation mouse
                {
                    TDropdown = CreateWindow("COMBOBOX", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,260, 40, 100, 150, hwnd, reinterpret_cast<HMENU>(1), NULL, NULL);
                    SendMessage(TDropdown, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Translate"));
                    SendMessage(TDropdown, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>("Scale"));
                }
                else if(index==4) //Clear screen
                {
                    vec.clear();
                    GetClientRect(hwnd, &clientRect);
                    CScreen=GetPixel(hdc,5,5);
                    hBrush = CreateSolidBrush(CScreen);
                    FillRect(hdc, &clientRect, hBrush);
                    DeleteObject(hBrush);
                }
                else if(index==5) //Save all data in screen
                {
                    MyFile.open("filename.txt");
                    clearFile("filename.txt");
                    for (long long i = 0; i < vec.size(); i++)
                    {
                        s = to_string(vec[i])+" ";
                        MyFile << s;
                    }
                    MyFile.close();
                }
                else if(index==6) //load data from files
                {
                    MyFile.open("filename.txt");
                    VEC.clear();
                    MyFile.seekg(0,ios::end);
                    if(MyFile.tellg()!=0)
                    {
                        MyFile.seekg(0,ios::beg);
                        getline(MyFile,c);
                        for(long long i=0; i<c.length()-1; i++)
                        {
                            v=c[i];
                            if(v!= " ")
                                x=x+v;
                            else if(v==" ")
                            {
                                VEC.push_back(std::stoi(x));
                                x="";
                            }
                        }
                        VEC.push_back(std::stoi(x));
                        x="";
                    }
                    MyFile.close();
                    while(count_vec<VEC.size())
                    {
                        if(VEC[count_vec]==7 || VEC[count_vec]==8 || VEC[count_vec]==9) //Line
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            if(VEC[count_vec]==7)
                                drawLineSimpleDDA(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], VEC[count_vec+5], tempColor);
                            else if(VEC[count_vec]==8)
                                drawLineMidPoint(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], VEC[count_vec+5], tempColor);
                            else if(VEC[count_vec]==9)
                                drawLineParametric(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], VEC[count_vec+5], tempColor);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);vec.push_back(VEC[count_vec+2]);
                            vec.push_back(VEC[count_vec+3]);vec.push_back(VEC[count_vec+4]);vec.push_back(VEC[count_vec+5]);
                            count_vec+=6;
                        }
                        else if(VEC[count_vec]==10 || VEC[count_vec]==11 || VEC[count_vec]==12 || VEC[count_vec]==13 || VEC[count_vec]==14) //Circle
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            if(VEC[count_vec]==10)
                                drawCircleDirect(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            else if(VEC[count_vec]==11)
                                drawCirclePolar(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            else if(VEC[count_vec]==12)
                                drawCircleIterativePolar(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            else if(VEC[count_vec]==13)
                                drawCircleMidpoint(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            else if(VEC[count_vec]==14)
                                drawCircleModifiedMidpoint(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);vec.push_back(VEC[count_vec+2]);
                            vec.push_back(VEC[count_vec+3]);vec.push_back(VEC[count_vec+4]);
                            count_vec+=5;
                        }
                        else if(VEC[count_vec]==15 || VEC[count_vec]==16) //Filling Circles
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            if(VEC[count_vec]==15)
                                fillingCircleWithLines(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            else if(VEC[count_vec]==16)
                                fillingCircleWithCircles(hdc, VEC[count_vec+2], VEC[count_vec+3], VEC[count_vec+4], tempColor);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);vec.push_back(VEC[count_vec+2]);
                            vec.push_back(VEC[count_vec+3]);vec.push_back(VEC[count_vec+4]);
                            count_vec+=5;
                        }
                        else if(VEC[count_vec]==17) //Filling Square
                        {
                            Rectangle(hdc, fillingsquare_xc-L, fillingsquare_yc-L, fillingsquare_xc+L, fillingsquare_yc+L);
                            fillingSquareHermitCurveVertical(hdc,fillingsquare_xc,fillingsquare_yc,L,fillingCol);
                            vec.push_back(VEC[count_vec]);
                            count_vec+=1;
                        }
                        else if(VEC[count_vec]==18) //Filling Rectangle
                        {
                            Rectangle(hdc, fillingrectangle_xc - halfW, fillingrectangle_yc - halfL, fillingrectangle_xc + halfW, fillingrectangle_yc + halfL);
                            drawBezierInRec(hdc,fillingrectangle_xc,fillingrectangle_yc,halfW,halfL,fillingCol);
                            vec.push_back(VEC[count_vec]);
                            count_vec+=1;
                        }
                        else if(VEC[count_vec]==19) //Convex
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            int j=0;
                            while(j<convex_num)
                            {
                                convex_P[j].x=VEC[count_vec];
                                vec.push_back(VEC[count_vec]);
                                count_vec++;
                                convex_P[j].y=VEC[count_vec];
                                vec.push_back(VEC[count_vec]);
                                count_vec++; j++;
                            }
                            ConvexFill(hdc,convex_P,convex_num, tempColor);
                        }
                        else if(VEC[count_vec]==20) //Non Convex
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            int j=0;
                            while(j<convex_num)
                            {
                                nonconvex_P[j].x=VEC[count_vec];
                                vec.push_back(VEC[count_vec]);
                                count_vec++;
                                nonconvex_P[j].y=VEC[count_vec];
                                vec.push_back(VEC[count_vec]);
                                count_vec++; j++;
                            }
                            GeneralPolygonFill(hdc,nonconvex_P,convex_num, color);
                        }
                        else if(VEC[count_vec]==21 || VEC[count_vec]==22) //Flood Fill
                        {
                            int temp=count_vec;
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            vec.push_back(VEC[count_vec]);
                            vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            int j=0;
                            while(j<flood_num)
                            {
                                flood_P[j].x=VEC[count_vec];
                                vec.push_back(VEC[count_vec]);
                                count_vec++;
                                flood_P[j].y=VEC[count_vec];
                                vec.push_back(VEC[count_vec]);
                                count_vec++;
                                j++;
                            }
                            DrawShape(hdc,flood_P,flood_num,tempColor);
                            if(VEC[temp]==21)
                                RecursiveFloodFill(hdc, VEC[count_vec], VEC[count_vec+1],tempColor, fillingCol);
                            else if(VEC[temp]==22)
                                NonRecursiveFloodFill(hdc, VEC[count_vec], VEC[count_vec+1],tempColor, fillingCol);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                        }
                        else if (VEC[count_vec]==23) //Cardinal Spline Curve
                        {
                            spline_v[0].x=VEC[count_vec+1]; spline_v[0].y=VEC[count_vec+2];
                            spline_v[1].x=VEC[count_vec+3]; spline_v[1].y=VEC[count_vec+4];
                            spline_v[2].x=VEC[count_vec+5]; spline_v[2].y=VEC[count_vec+6];
                            spline_v[3].x=VEC[count_vec+7]; spline_v[3].y=VEC[count_vec+8];
                            DrawCardinalSpline(hdc,spline_v,4,0.001,4);
                            vec.push_back(VEC[count_vec]); vec.push_back(VEC[count_vec+1]);vec.push_back(VEC[count_vec+2]);
                            vec.push_back(VEC[count_vec+3]); vec.push_back(VEC[count_vec+4]); vec.push_back(VEC[count_vec+5]);
                            vec.push_back(VEC[count_vec+6]); vec.push_back(VEC[count_vec+7]); vec.push_back(VEC[count_vec+8]);
                            count_vec+=9;
                        }
                        else if(VEC[count_vec]==24 || VEC[count_vec]==25 || VEC[count_vec]==26) //Ellipse
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            if(VEC[count_vec]==24)
                                EllipseDirect(hdc,VEC[count_vec+2],VEC[count_vec+3],ellipse_A,ellipse_B,tempColor);
                            else if(VEC[count_vec]==25)
                                EllipsePolar(hdc,VEC[count_vec+2],VEC[count_vec+3],ellipse_A,ellipse_B,tempColor);
                            else if(VEC[count_vec]==26)
                                EllipseMidPoint(hdc,VEC[count_vec+2],VEC[count_vec+3],ellipse_A,ellipse_B,tempColor);
                            vec.push_back(VEC[count_vec]);
                            vec.push_back(VEC[count_vec+1]);
                            vec.push_back(VEC[count_vec+2]);
                            vec.push_back(VEC[count_vec+3]);
                            count_vec+=4;
                        }
                        else if(VEC[count_vec]==27) //Clipping Point
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            x_left=70,y_top=50,x_right=220,y_bottom=300;
                            Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            while(VEC[count_vec]!=-27)
                            {
                                PointClipping(hdc,VEC[count_vec],VEC[count_vec+1],x_left,y_top,x_right,y_bottom,tempColor);
                                vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                                count_vec+=2;
                            }
                            vec.push_back(VEC[count_vec]); count_vec++;
                        }
                        else if(VEC[count_vec]==30) //Clipping Point
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            x_left=250,y_top=100,x_right=400,y_bottom=250;
                            Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            while(VEC[count_vec]!=-30)
                            {
                                PointClipping(hdc,VEC[count_vec],VEC[count_vec+1],x_left,y_top,x_right,y_bottom,tempColor);
                                vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                                count_vec+=2;
                            }
                            vec.push_back(VEC[count_vec]); count_vec++;
                        }
                        else if(VEC[count_vec]==28) //Clipping Line
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            x_left=70,y_top=50,x_right=220,y_bottom=300;
                            Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            while(VEC[count_vec]!=-28)
                            {
                                LineClipping(hdc,VEC[count_vec],VEC[count_vec+1],VEC[count_vec+2],VEC[count_vec+3],x_left,y_top,x_right,y_bottom);
                                vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);vec.push_back(VEC[count_vec+2]);vec.push_back(VEC[count_vec+3]);
                                count_vec+=4;
                            }
                            vec.push_back(VEC[count_vec]); count_vec++;
                        }
                        else if(VEC[count_vec]==31) //Clipping Line
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            x_left=250,y_top=100,x_right=400,y_bottom=250;
                            Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            while(VEC[count_vec]!=-31)
                            {
                                LineClipping(hdc,VEC[count_vec],VEC[count_vec+1],VEC[count_vec+2],VEC[count_vec+3],x_left,y_top,x_right,y_bottom);
                                vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);vec.push_back(VEC[count_vec+2]);vec.push_back(VEC[count_vec+3]);
                                count_vec+=4;
                            }
                            vec.push_back(VEC[count_vec]); count_vec++;
                        }
                        else if(VEC[count_vec]==29) //Clipping Polygon
                        {
                            tempColor = checkNumOfColor(VEC[count_vec+1]);
                            x_left=70,y_top=50,x_right=220,y_bottom=300;
                            Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                            vec.push_back(VEC[count_vec]);vec.push_back(VEC[count_vec+1]);
                            count_vec+=2;
                            while(VEC[count_vec]!=-29)
                            {
                                int j=0;
                                while(j<clippingpolygon_num)
                                {
                                    clippingpolygon_P[j].x=VEC[count_vec];
                                    vec.push_back(VEC[count_vec]);
                                    count_vec++;
                                    clippingpolygon_P[j].y=VEC[count_vec];
                                    vec.push_back(VEC[count_vec]);
                                    count_vec++;
                                    j++;
                                }
                                PolygonClip(hdc,clippingpolygon_P,clippingpolygon_num,x_left,y_top,x_right,y_bottom);
                            }
                            vec.push_back(VEC[count_vec]); count_vec++;
                        }
                    }

                    count_vec=0;
                }
                if(index!=3) //remove color menu
                    DestroyWindow(colorComboBox);
                if(index!=2) //remove color menu
                    DestroyWindow(hDropdown);
                if(index!=32) //remove transformation menu
                    DestroyWindow(TDropdown);
            }
            else if (lParam == (LPARAM)colorComboBox && HIWORD(wParam) == CBN_SELCHANGE) //color menu
            {
                colorIndex = SendMessage(colorComboBox,CB_GETCURSEL,0,0);
                cout<<"colorIndex = "<<colorIndex<<endl;
                if(colorIndex==0) //Red
                    color = RGB(255, 15, 20);
                else if(colorIndex==1) //Blue
                    color = RGB(0, 0, 255);
                else if(colorIndex==2) //Brown
                    color = RGB(50, 0, 20);
                else if(colorIndex==3) //Black
                    color = RGB(0, 0, 0);
                else if(colorIndex==4) //Purple
                    color = RGB(112, 73, 179);
            }
            else if (lParam == (LPARAM)hDropdown && HIWORD(wParam) == CBN_SELCHANGE) //mouse menu
            {
                int nSelectedIndex = SendMessage(hDropdown, CB_GETCURSEL, 0, 0);
                if (nSelectedIndex != nLastSelectedIndex)
                {
                    switch (nSelectedIndex)
                    {
                    case 0:
                        hCursorD = hCursorArrow;
                        break;
                    case 1:
                        hCursorD = hCursorHand;
                        break;
                    case 2:
                        hCursorD = hCursorCrosshair;
                        break;
                    }
                    SetCursor(hCursorD);
                    nLastSelectedIndex = nSelectedIndex;
                }
            }
            else if (lParam == (LPARAM)TDropdown && HIWORD(wParam) == CBN_SELCHANGE) //transformation menu
            {
                transformationIndex = SendMessage(TDropdown,CB_GETCURSEL,0,0);
                cout<<"transformation Index = "<<transformationIndex<<endl;
            }
            break;
        }

    case WM_LBUTTONDOWN:
        // Line
        if(index==7 || index==8 || index==9)
        {
            if(line_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                line_xs=LOWORD(lParam);
                line_ys=HIWORD(lParam);
                trans_xs=line_xs;
                trans_ys=line_ys;
                cout<<"t "<<trans_xs<<" "<<trans_ys<<endl;
                vec.push_back(line_xs);
                vec.push_back(line_ys);
                line_count++;
            }
            else if(line_count==1)
            {
                line_xe=LOWORD(lParam);
                line_ye=HIWORD(lParam);
                trans_xe=line_xe;
                trans_ye=line_ye;
                cout<<"t1 "<<trans_xe<<" "<<trans_ye<<endl;
                vec.push_back(line_xe);
                vec.push_back(line_ye);
                if(index==7)
                    drawLineSimpleDDA(hdc, line_xs, line_ys, line_xe, line_ye, color); //parametric
                else if(index==8)
                    drawLineMidPoint(hdc, line_xs, line_ys, line_xe, line_ye, color); //MidPoint
                else if(index==9)
                    drawLineParametric(hdc, line_xs, line_ys, line_xe, line_ye, color); //DDA
                line_count=0;
                ReleaseDC(hwnd, hdc);
            }
        }
        //-------------------------------------------------------------------------------------------------
        // Circle
        if(index==10 || index==11 || index==12 || index==13 || index==14)
        {
            if(circle_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                circle_xs=LOWORD(lParam);
                circle_ys=HIWORD(lParam);
                vec.push_back(circle_xs);
                vec.push_back(circle_ys);
                circle_count++;
            }
            else if(circle_count==1)
            {
                circle_xe=LOWORD(lParam);
                circle_ye=HIWORD(lParam);
                circle_r = round(sqrt(pow((circle_xe-circle_xs),2)+(pow((circle_ye-circle_ys),2))));
                vec.push_back(circle_r);
                if(index==10)
                    drawCircleDirect(hdc, circle_xs, circle_ys, circle_r, color);
                else if(index==11)
                    drawCirclePolar(hdc, circle_xs, circle_ys, circle_r, color);
                else if(index==12)
                    drawCircleIterativePolar(hdc, circle_xs, circle_ys, circle_r, color);
                else if(index==13)
                    drawCircleMidpoint(hdc, circle_xs, circle_ys, circle_r, color);
                else if(index==14)
                    drawCircleModifiedMidpoint(hdc, circle_xs, circle_ys, circle_r, color);
                circle_count=0;
                ReleaseDC(hwnd, hdc);
            }
        }
        //-------------------------------------------------------------------------------------------------
        //Filling Circle with Lines or Circles
        if(index==15 || index==16)
        {
            if(filling_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                filling_xs = LOWORD(lParam);
                filling_ys = HIWORD(lParam);
                vec.push_back(filling_xs);
                vec.push_back(filling_ys);
                filling_count++;
            }
            else if(filling_count==1)
            {
                filling_xe = LOWORD(lParam);
                filling_ye = HIWORD(lParam);
                filling_r = round(sqrt(pow((filling_xe-filling_xs),2)+(pow((filling_ye-filling_ys),2))));
                vec.push_back(filling_r);
                if(index==15)
                    fillingCircleWithLines(hdc, filling_xs, filling_ys, filling_r, color);
                else if(index==16)
                    fillingCircleWithCircles(hdc, filling_xs, filling_ys, filling_r, color);
                ReleaseDC(hwnd, hdc);
                filling_count=0;
            }
        }
        //-------------------------------------------------------------------------------------------------
        //Filling Square with Hermit Curve[Vertical]
        if(index==17)
        {
            Rectangle(hdc, fillingsquare_xc-L, fillingsquare_yc-L, fillingsquare_xc+L, fillingsquare_yc+L);
            fillingSquareHermitCurveVertical(hdc,fillingsquare_xc,fillingsquare_yc,L,fillingCol);
            vec.push_back(index);
        }
        //Filling Rectangle with Bezier Curve[horizontal]
        if(index==18)
        {
            Rectangle(hdc, fillingrectangle_xc - halfW, fillingrectangle_yc - halfL, fillingrectangle_xc + halfW, fillingrectangle_yc + halfL);
            drawBezierInRec(hdc,fillingrectangle_xc,fillingrectangle_yc,halfW,halfL,fillingCol);
            vec.push_back(index);
        }
        //-------------------------------------------------------------------------------------------------
        //Convex
        if(index==19)
        {
            if(convex_cnt==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
            }
            convex_P[convex_cnt].x=LOWORD(lParam);
            convex_P[convex_cnt].y=HIWORD(lParam);
            vec.push_back(convex_P[convex_cnt].x);
            vec.push_back(convex_P[convex_cnt].y);
            if (convex_cnt==(convex_num-1))
            {
                ConvexFill(hdc,convex_P,convex_num, color);
                ReleaseDC(hwnd,hdc);
                convex_cnt=0;
            }
            else
                convex_cnt++;
        }
        //Non Convex
        if(index==20)
        {
            if(nonconvex_cnt==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
            }
            nonconvex_P[nonconvex_cnt].x=LOWORD(lParam);
            nonconvex_P[nonconvex_cnt].y=HIWORD(lParam);
            vec.push_back(nonconvex_P[nonconvex_cnt].x);
            vec.push_back(nonconvex_P[nonconvex_cnt].y);
            if (nonconvex_cnt==(convex_num-1))
            {
                GeneralPolygonFill(hdc,nonconvex_P,convex_num, color);
                ReleaseDC(hwnd,hdc);
                nonconvex_cnt=0;
            }
            else
                nonconvex_cnt++;
        }
        //-------------------------------------------------------------------------------------------------
        //Flood Fill
        if(index==21 || index==22)
        {
            if (flood_count==0)
            {
                if(flood_cnt==0)
                {
                    vec.push_back(index);
                    vec.push_back(checkColor(color));
                }
                flood_P[flood_cnt].x=LOWORD(lParam);
                flood_P[flood_cnt].y=HIWORD(lParam);
                vec.push_back(flood_P[flood_cnt].x);
                vec.push_back(flood_P[flood_cnt].y);
                if (flood_cnt==(flood_num-1))
                {
                    DrawShape(hdc,flood_P,flood_num,color);
                    flood_cnt=0;
                    flood_count++;
                }
                else
                    flood_cnt++;
            }
            else if(flood_count==1)
            {
                flood_x = LOWORD(lParam);
                flood_y = HIWORD(lParam);
                vec.push_back(flood_x);
                vec.push_back(flood_y);
                if(index==21)
                    RecursiveFloodFill(hdc, flood_x, flood_y,color, fillingCol);
                else if(index==22)
                    NonRecursiveFloodFill(hdc, flood_x, flood_y,color, fillingCol );
                flood_count=0;
                ReleaseDC(hwnd,hdc);
            }
        }
        //Cardinal Spline Curve
        if(index==23)
        {
            if(spline_cnt == 0){
                spline_v[0].x = LOWORD(lParam);
                spline_v[0].y = HIWORD(lParam);
                spline_cnt+=1;
            }
            else if (spline_cnt == 1){

                spline_v[1].x = LOWORD(lParam);
                spline_v[1].y = HIWORD(lParam);
                spline_cnt+=1;
            }
            else if (spline_cnt == 2){

                spline_v[3].x = LOWORD(lParam);
                spline_v[3].y = HIWORD(lParam);
                spline_cnt+=1;
            }
            else if (spline_cnt == 3){
                spline_v[2].x = LOWORD(lParam);
                spline_v[2].y = HIWORD(lParam);
                DrawCardinalSpline(hdc,spline_v,4,0.001,4);
                ReleaseDC(hwnd,hdc);
                spline_cnt=0;
                vec.push_back(index);vec.push_back(spline_v[0].x);vec.push_back(spline_v[0].y);
                vec.push_back(spline_v[1].x);vec.push_back(spline_v[1].y);
                vec.push_back(spline_v[2].x);vec.push_back(spline_v[2].y);
                vec.push_back(spline_v[3].x);vec.push_back(spline_v[3].y);
            }
        }
        //-------------------------------------------------------------------------------------------------
        //Ellipse
        if(index==24 || index==25 ||index==26)
        {
            vec.push_back(index);
            vec.push_back(checkColor(color));
            ellipse_xc = LOWORD(lParam);
            ellipse_yc = HIWORD(lParam);
            vec.push_back(ellipse_xc);
            vec.push_back(ellipse_yc);
            if(index==24)
                EllipseDirect(hdc,ellipse_xc,ellipse_yc,ellipse_A,ellipse_B,color);
            else if(index==25)
                EllipsePolar(hdc,ellipse_xc,ellipse_yc,ellipse_A,ellipse_B,color);
            else if(index==26)
                EllipseMidPoint(hdc,ellipse_xc,ellipse_yc,ellipse_A,ellipse_B,color);
        }
        //-------------------------------------------------------------------------------------------------
        //Clipping Point (Rectangle)
        if(index==27)
        {
            if(clippingpoint_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                x_left=70,y_top=50,x_right=220,y_bottom=300;
                Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                clippingpoint_count++;
            }
            else if(clippingpoint_count==1)
            {
                clippingpoint_xs = LOWORD(lParam);
                clippingpoint_ys = HIWORD(lParam);
                vec.push_back(clippingpoint_xs);
                vec.push_back(clippingpoint_ys);
                PointClipping(hdc,clippingpoint_xs,clippingpoint_ys,x_left,y_top,x_right,y_bottom,color);
                clippingpoint_count=1;
                ReleaseDC(hwnd, hdc);
            }
        }
        //Clipping Point (Square)
        if(index==30)
        {
            if(clippingpoint1_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                x_left=250,y_top=100,x_right=400,y_bottom=250;
                Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                clippingpoint1_count++;
            }
            else if(clippingpoint1_count==1)
            {
                clippingpoint_xs = LOWORD(lParam);
                clippingpoint_ys = HIWORD(lParam);
                vec.push_back(clippingpoint_xs);
                vec.push_back(clippingpoint_ys);
                PointClipping(hdc,clippingpoint_xs,clippingpoint_ys,x_left,y_top,x_right,y_bottom,color);
                clippingpoint1_count=1;
                ReleaseDC(hwnd, hdc);
            }
        }
        //Clipping Line (Rectangle)
        if(index==28)
        {
            if(clippingline_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                x_left=70,y_top=50,x_right=220,y_bottom=300;
                Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                clippingline_count++;

            }
            else if(clippingline_count==1)
            {
                clippingline_xs = LOWORD(lParam);
                clippingline_ys = HIWORD(lParam);
                vec.push_back(clippingline_xs);
                vec.push_back(clippingline_ys);
                clippingline_count++;
            }
            else if(clippingline_count==2)
            {
                clippingline_xe = LOWORD(lParam);
                clippingline_ye = HIWORD(lParam);
                vec.push_back(clippingline_xe);
                vec.push_back(clippingline_ye);
                LineClipping(hdc,clippingline_xs,clippingline_ys,clippingline_xe,clippingline_ye,x_left,y_top,x_right,y_bottom);
                clippingline_count=1;
                ReleaseDC(hwnd, hdc);
            }
        }
        //Clipping Line (Square)
        if(index==31)
        {
            if(clippingline1_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                //using Rectangle
                x_left=250,y_top=100,x_right=400,y_bottom=250;
                Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                clippingline1_count++;
            }
            else if(clippingline1_count==1)
            {
                clippingline_xs = LOWORD(lParam);
                clippingline_ys = HIWORD(lParam);
                vec.push_back(clippingline_xs);
                vec.push_back(clippingline_ys);
                clippingline1_count++;
            }
            else if(clippingline1_count==2)
            {
                clippingline_xe = LOWORD(lParam);
                clippingline_ye = HIWORD(lParam);
                vec.push_back(clippingline_xe);
                vec.push_back(clippingline_ye);
                LineClipping(hdc,clippingline_xs,clippingline_ys,clippingline_xe,clippingline_ye,x_left,y_top,x_right,y_bottom);
                clippingline1_count=1;
                ReleaseDC(hwnd, hdc);
            }
        }
        //Clipping Polygon (Rectangle)
        if(index==29)
        {
            if(clippingpolygon_count==0)
            {
                vec.push_back(index);
                vec.push_back(checkColor(color));
                x_left=70,y_top=50,x_right=220,y_bottom=300;
                Rectangle(hdc,x_left,y_top,x_right,y_bottom);
                clippingpolygon_count++;
            }
            else if(clippingpolygon_count==1)
            {
                clippingpolygon_P[clippingpolygon_cnt].x=LOWORD(lParam);
                clippingpolygon_P[clippingpolygon_cnt].y=HIWORD(lParam);
                vec.push_back(clippingpolygon_P[clippingpolygon_cnt].x);
                vec.push_back(clippingpolygon_P[clippingpolygon_cnt].y);
                if (clippingpolygon_cnt==(clippingpolygon_num-1))
                {
                    PolygonClip(hdc,clippingpolygon_P,clippingpolygon_num,x_left,y_top,x_right,y_bottom);
                    clippingpolygon_cnt=0;
                    ReleaseDC(hwnd,hdc);
                }
                else
                    clippingpolygon_cnt++;

                clippingpolygon_count=1;
            }
        }
        //-------------------------------------------------------------------------------------------------
        //Transformation
        if(index==32)
        {
            startLine.setValue(trans_xe,trans_ye);
            endLine.setValue(trans_xs,trans_ys);
            if(transformationIndex==0)
            {
                // Draw the transformed line
                translationMatrix = translate(translate_x, translate_y);
                transformedStart = translationMatrix * startLine;
                transformedEnd = translationMatrix * endLine;
                drawLineSimpleDDA(hdc,transformedStart[0],transformedStart[1],transformedEnd[0],transformedEnd[1],color);
            }
            else if(transformationIndex==1)
            {
                // Draw the Scaled line
                scaleMatrix = scale(scale_x, scale_y);
                scaleformedStart = scaleMatrix * startLine;
                scaleformedEnd = scaleMatrix * endLine;
                drawLineSimpleDDA(hdc,scaleformedStart[0],scaleformedStart[1],scaleformedEnd[0],scaleformedEnd[1],color);
            }
        }
        break;

    case WM_SETCURSOR:
    {
        // Only update the cursor when the mouse is over the combo box
        if (LOWORD(lParam) == HTCLIENT )
        {
            switch (nLastSelectedIndex)
            {
            case 0:
                SetCursor(hCursorArrow);
                break;
            case 1:
                SetCursor(hCursorHand);
                break;
            case 2:
                SetCursor(hCursorCrosshair);
                break;
            }
            return TRUE; // Tell Windows we handled the message
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
