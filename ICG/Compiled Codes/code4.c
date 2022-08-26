

// print grades
// >=80->A,>=70->B,>=60->C,>=40->D,ELSE F
int ch;
int main(){
	int num;
	int a,b,c,d,f;
	a=65;
	b=66;
	c=67;
	d=68;
	f=70;
	num=-65;
	if(num>=80){
		ch=a;
	}else{
		if(num>=70){
			ch=b;
		}else{
			if(num>=60){
				ch=c;
			}else{
				if(num>=40){
					ch=d;
				}else{
					ch=f;
				}
			}
		}
	}
	printchar(ch);
}