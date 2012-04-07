.assembly extern mscorlib {} 
.assembly output
{
.ver  0:0:0:0
}
.module new.exe
.class public auto ansi beforefieldinit myclass extends [mscorlib]System.Object
{
.method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed 
{
	.maxstack 8
	ldarg.0
	call instance void object::'.ctor'()
	ret
}
.method static int32 myfun(int32  x ,int32  y ) cil managed
{
.maxstack 50
.locals init(bool  t )
.locals init(int32  p ,int32  a ,int32  b )
ldc.i4 0 
brtrue l1
ldc.i4 1 
br.s l2
l1: ldc.i4.1 
l2: stloc t
ldc.i4 200 
stloc a
ldc.i4 1 
stloc b
ldloc a 
ldloc b 
ldc.i4.s 0x1f
and
shl
stloc p
ldloc p 
call void [mscorlib]System.Console::WriteLine(int32)
ldloc b 
ret 
}
.method static void lc() cil managed
{
.maxstack 50
pop 
ret 
}
.method static void main() cil managed
{
 .entrypoint
.maxstack 50
ldc.i4 1 
ldc.i4 2 
call int32 class myclass::myfun (  int32 , int32  )  
pop 
ret 
}
}
.class public auto ansi beforefieldinit my2 extends [mscorlib]System.Object
{
.method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed 
{
	.maxstack 8
	ldarg.0
	call instance void object::'.ctor'()
	ret
}
.method static void lc1() cil managed
{
.maxstack 50
pop 
ret 
}
}
