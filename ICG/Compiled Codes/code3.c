
// print all factors of a number n

int count;
int main(){
	int n;
	n=36;
	count=1;
	while (count<=n)
	{
		if((n%count)==0){
			println(count);
		}
		count++;
	}
	
}