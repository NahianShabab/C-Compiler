

// print weighted sum of two array of marks.
// weighted_sum[i]=m1[i]*4+m2[i]*6;
int m1[10];

int count;
int main(){
	count=10;
	int m2[10];
	m1[0]=9;
	m1[1]=10;
	m1[2]=8;
	m1[3]=7;
	m1[4]=8;
	m1[5]=6;
	m1[6]=3;
	m1[7]=9;
	m1[8]=6;
	m1[9]=5;

	m2[0]=6;
	m2[1]=7;
	m2[2]=9;
	m2[3]=5;
	m2[4]=6;
	m2[5]=8;
	m2[6]=4;
	m2[7]=1;
	m2[8]=0;
	m2[9]=7;
	int weighted_sum[10];
	while(count){
		count=count-1;
		weighted_sum[count]=m1[count]*4+m2[count]*6;
	}
	count=10;
	int a;
	while(count){
		count--;
		a=weighted_sum[count];
		println(a);
	}
}