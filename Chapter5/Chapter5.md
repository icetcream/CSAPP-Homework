## 5.13 

A:
   xmm0               rcx
     |                  |
     |         |- load-
     |         |        |
     |         |- load- 
     |      multi       |
    add--------|      add
     |                  |
     |                  |
   xmm0                 rcx

B:
    浮点数加法的延迟

C:
    整数加法的延迟

D:
    因为乘法可以流水线
    主要是浮点数加法，这个有前后依赖不能流水线

## 5.14
```c
void inner4(vec_ptr u,vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    
    for(i=0;i<length-5;i+=6){
        sum = sum+udata[i]*vdata[i];
        sum = sum+udata[i+1]*vdata[i+1];
        sum = sum+udata[i+2]*vdata[i+2];
        sum = sum+udata[i+3]*vdata[i+3];
        sum = sum+udata[i+4]*vdata[i+4];
        sum = sum+udata[i+5]*vdata[i+5];
    }
    
    for(;i<length;i++){
        sum = sum+udata[i]*vdata[i];
    }
    *dest=sum;
}

```
A:
    无论是哪种类型，关键路径上的加法都有依赖性，所以不能限制就是这个的延迟
B:
    关键路径上的浮点数加法有依赖，最少的CPE也要3

## 5.15
```C
void inner4(vec_ptr u,vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;
    data_t sum1 = (data_t) 0;
    data_t sum2 = (data_t) 0;
    data_t sum3 = (data_t) 0;
    data_t sum4 = (data_t) 0;
    data_t sum5 = (data_t) 0;
    
    for(i=0;i<length-5;i+=6){
        sum = sum+udata[i]*vdata[i];
        sum1 = sum+udata[i+1]*vdata[i+1];
        sum2 = sum+udata[i+2]*vdata[i+2];
        sum3 = sum+udata[i+3]*vdata[i+3];
        sum4 = sum+udata[i+4]*vdata[i+4];
        sum5 = sum+udata[i+5]*vdata[i+5];
    }
    
    for(;i<length;i++){
        sum = sum+udata[i]*vdata[i];
    }
    *dest=sum+sum1+sum2+sum3+sum4+sum5;
}
```

整数是被乘法限制了，乘法流水线最快的CPE也只有1.0
浮点数是被浮点数加法限制了，浮点数的加法最快CPE也是只有1.0

## 5.16
```C
void inner4(vec_ptr u,vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    
    for(i=0;i<length-5;i+=6){
        sum = sum+udata[i]*vdata[i]
        +udata[i+1]*vdata[i+1]
        +udata[i+2]*vdata[i+2]
        +udata[i+3]*vdata[i+3]
        +udata[i+4]*vdata[i+4]
        +udata[i+5]*vdata[i+5];
    }
    
    for(;i<length;i++){
        sum = sum+udata[i]*vdata[i];
    }
    *dest=sum;
}
```



## 5.17

```c

void memset(void *s,unsigned int c, size_t n){
    int K = sizeof(unsigned long);
    size_t cnt = 0;
    unsigned char* schar = s;
    int rsK = K/8;

    if(n < K){
        while(cnt < n){
            *schar++ = (unsigned char)c;
            cnt++;
        }
    }else{
        unsigned long word = 0;
        for(int i = 0; i < 8; i++){
            word <<= rsK;
            word += (unsigned char)c;
        }
        int nNearK = n/K*K;
        unsigned long* longWord = s;
        while(cnt < nNear){
            *longWord++ = word;
            cnt += K;
        }
        while(cnt < n){
            *schar++ = (unsigned char)c;
            cnt++;
        }
    }
}
```


## 5.18

result和xpwr都依赖上一次循环，但是关键路径是xpwr
K>=L*C

```c

double efficient_poly(double a[],double x,long degree){
    long i;
	double result1 = a[0];
	double result2 = 0;
	double result3 = 0;
	double result4 = 0;
	double result5 = 0;
	double result6 = 0;
	double result7 = 0;
	double result8 = 0;
	double result9 = 0;
	double result10 = 0;

	double xpwr1 = x;
	double xpwr2 = xpwr1 * x;
	double xpwr3 = xpwr2 * x;
	double xpwr4 = xpwr3 * x;
	double xpwr5 = xpwr4 * x;
	double xpwr6 = xpwr5 * x;
	double xpwr7 = xpwr6 * x;
	double xpwr8 = xpwr7 * x;
	double xpwr9 = xpwr8 * x;
	double xpwr10 = xpwr9 * x;
	double x10 = xpwr10;

	for (i = 1; (i+9) <= degree; i += 10)
	{
		result1 += a[i] * xpwr1;
		result2 += a[i+1] * xpwr2;
		result3 += a[i+2] * xpwr3;
		result4 += a[i+3] * xpwr4;
		result5 += a[i+4] * xpwr5;
		result6 += a[i+5] * xpwr6;
		result7 += a[i+6] * xpwr7;
		result8 += a[i+7] * xpwr8;
		result9 += a[i+8] * xpwr9;
		result10 += a[i+9] * xpwr10;

		xpwr1 *= x10;
		xpwr2 *= x10;
		xpwr3 *= x10;
		xpwr4 *= x10;
		xpwr5 *= x10;
		xpwr6 *= x10;
		xpwr7 *= x10;
		xpwr8 *= x10;
		xpwr9 *= x10;
		xpwr10 *= x10;
	}
	for (; i <= degree; ++i)
	{
		result1 += a[i] * xpwr1;
		xpwr1 *= x;
	}
	
	result1 += result2;
	result1 += result3;
	result1 += result4;
	result1 += result5;
	result1 += result6;
	result1 += result7;
	result1 += result8;
	result1 += result9;
	result1 += result10;
	return result1;
}



```


## 5.19

```c
void psum3(float a[], float p[], long n){
    long i;
    p[0] = a[0];
    for(i=1; (i+2)<=n; i+=3){
        p[i] = p[i-1] + a[i];
        p[i+1] = p[i-1] + a[i] + a[i+1];
        p[i+2] = p[i-1] + a[i] + a[i+1] + a[i+2];
    }

    for(; i<=n; i++){
        p[i] = p[i-1]+a[i];
    }

}