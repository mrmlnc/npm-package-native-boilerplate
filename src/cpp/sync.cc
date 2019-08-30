#include <nan.h>

namespace SumSyncMethod {
using v8::Local;
using v8::Number;

NAN_METHOD(sum)
{
	if (!info[0]->IsNumber()) {
		return Nan::ThrowTypeError("the first argument must be a number");
	}
	if (!info[1]->IsNumber()) {
		return Nan::ThrowTypeError("the second argument must be a number");
	}

	double a = Nan::To<double>(info[0]).FromJust();
	double b = Nan::To<double>(info[1]).FromJust();

	double result;

	int status = Sum::sum(a, b, result);

	info.GetReturnValue().Set(result);
}
}
