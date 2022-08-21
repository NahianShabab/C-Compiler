int foo(int a){
	int i;
	if(a== 0){
		return 1;
	}i=a;
	return foo(a-1)+i;
}

int main(){
	int i;
 
	i = foo(7);
	println(i);
 
	return 0;
}
