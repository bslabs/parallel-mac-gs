/* general definition of these two types, if you'd like to put them in */
/* your types.r and typesiigs.r files */
type 'RECT' {
		longint = $$Countof(RectArray);
		array RectArray {
				Rect;		
		};
};
type 'pont' {
		longint = $$Countof(PointArray);
		array PointArray {
				Point;		
		};
};