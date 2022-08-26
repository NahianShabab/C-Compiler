int m2[6];
int count;

int main(){
	int m1[6];
	m1[0]=10;
	m1[1]=8;
	m1[2]=7;
	m1[3]=9;
	m1[4]=5;
	m1[5]=9;

	m2[0]=7;
	m2[1]=7;
	m2[2]=6;
	m2[3]=5;
	m2[4]=8;
	m2[5]=8;

	count=6;
	int weighted_sum[6];
	while (count)
	{
		count--;
		weighted_sum[count]=m1[count]*4+m2[count]*6;
	}
	weighted_sum[2];
}