extern int ext;

int weak;
int strong = 1;
__attribute__((weak)) weak2 = 2;
__attribute__((weakref)) void foo();

int main()
{
	if(foo) foo();
	return 0;
}
