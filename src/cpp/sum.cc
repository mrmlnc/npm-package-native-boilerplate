#include <nan.h>

namespace Sum {
int
sum(double a, double b, double& result)
{
	result = a + b;

	return 0;
}
}
