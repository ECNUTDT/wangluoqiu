#include "/usr/local/include/pbc/pbc.h"
#include "/usr/local/include/pbc/pbc_test.h"
#include <stdio.h>
int main(int argc, char **argv)
{
	pairing_t pairing;
	//声明一个配对类型的变量pairing
	element_t g,g1,g2,v,y,z;
	//声明一系列元素类型变量
    element_t arrN[6];
    element_t arrM[5];
    element_t arrV[5];
	element_t A;
	pbc_demo_pairing_init(pairing,argc,argv);
	//以文件流的方式输入参数
	

    element_init_G1(g,pairing);
	//初始化g为G1上元素
	element_init_G1(g1,pairing);
	//初始化g1为G1上元素
	element_init_G1(g2,pairing);
	//初始化g2为G1上元素
	element_init_G1(v,pairing);
	//初始化v为G1上元素
    element_init_Zr(z,pairing);
    //初始化z为Zr上元素
	element_init_Zr(y,pairing);
	//初始化y为Zr上元素
	element_init_GT(A,pairing);
	//初始化A为GT上元素
    element_random(g);
    element_random(g2);
    element_random(y);
    element_random(z);
    //定义g g2 y z为随机数
    element_pow_zn(g1,g,y);
    element_pow_zn(v,g,z);
    //执行指数运算



    if(freopen("../../data/setup_data/PP","w",stdout)==NULL)
    {
        fprintf(stderr,"error redirecting stdout\n");
    }
    //文件流输出
    printf("{\n");
    element_printf("\"g1\":\"%B\"\n",g1);
    //输出g1
    element_printf("\"g2\":\"%B\"\n",g2);
    //输出g2
    for(int i=0;i<6;i++)
    {
        element_init_G1(arrN[i],pairing);
        element_random(arrN[i]);
        element_printf("\"t%d\":\"%B\"\n",i+1,arrN[i]);
    }
    //输出t1-t6
    element_pow_zn(v,g,z);
    element_printf("\"v\":\"%B\"\n",v);
    for(int i=0;i<5;i++)
    {
        element_init_G1(arrM[i],pairing);
        element_init_Zr(arrV[i],pairing);
        element_random(arrM[i]);
        element_pow_zn(arrV[i],g,arrM[i]);
        element_printf("\"v%d\":\"%B\"\n",i+1,arrV[i]);
    }
    //输出v1-v5
    pairing_apply(A,g1,g2,pairing);
    //配对运算
    element_printf("\"A\":\"%B\"\n",A);
    //输出A
    printf("}\n");
    fclose(stdout);


    if(freopen("../../data/setup_data/MK","w",stdout)==NULL)
    {
        fprintf(stderr,"error redirecting stdout\n");
    }
    printf("{");
    element_printf("\"y\":\"%B\"",y);
    printf("}");
    fclose(stdout);
    element_clear(g);
    element_clear(g1);
    element_clear(g2);
    element_clear(z);
    element_clear(y);
    element_clear(v);
    element_clear(A);
    pairing_clear(pairing);
    return 0;

}
