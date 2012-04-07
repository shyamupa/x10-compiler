.assembly extern mscorlib {} 
.assembly output
{
.ver  0:0:0:0
}
.module newfile.exe
.class public auto ansi beforefieldinit myclass extends [mscorlib]System.Object
{
.method public hidebysig specialname rtspecialname instance default void '.ctor' ()  cil managed 
{
	.maxstack 8
	ldarg.0
	call instance void object::'.ctor'()
	ret
}
.method static void myfun() cil managed
{
.maxstack 50
.locals init(int32  V4 )
l16: 
l15: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l14: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l13: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l12: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l11: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l10: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l9: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l8: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l7: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l6: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l5: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l4: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l3: 
ldc.i4 7 
call void [mscorlib]System.Console::WriteLine(int32)
l2: 
ret 
l1:
}
.method static void main() cil managed
{
 .entrypoint
.maxstack 50
.locals init (class [mscorlib]System.Threading.Thread V6)
ldnull
ldftn void class myclass::myfun()
newobj instance void class [mscorlib]System.Threading.ThreadStart::'.ctor'(object, native int)
newobj instance void class [mscorlib]System.Threading.Thread::'.ctor'(class [mscorlib]System.Threading.ThreadStart)
stloc V6
ldloc V6
callvirt instance void class [mscorlib]System.Threading.Thread::Start()
l28: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l27: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l26: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l25: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l24: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l23: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l22: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l21: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l20: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l19: 
ldc.i4 6 
call void [mscorlib]System.Console::WriteLine(int32)
l18: 
ret 
l17:
}
}
