# assembly-n 使用向导 #
#简介：
>assembly-n是基于C++的虚拟机，在虚拟机上可以直接运行assembly-n汇编语言，未来assembly-n将作为program-n的中间语言。在本文中assembly-n简称为asn。


# 一、使用assembly-n #

----------
## 1、在Windows平台上使用 ##
1. `下载`[assembly-n源码](https://github.com/CrystalGrape/assembly-n/archive/master.zip "assembly-n源码")。
2. `使用vs2015打开工程(如果是其他版本的vs，可以在工程属性里修改平台工具集)。`
3. `编译。`
4. `使用assembly-n [namespace]运行asn。`


## 2、在Linux平台上使用 ##
1. `git clone https://github.com/CrystalGrape/assembly-n`
2. `编译ExternalCall.cpp:g++ -c ExternalCall.cpp -DLINUX`
3. `make`
4. `使用assembly-n [namespace]运行asn。`


# 二、使用asn汇编 #

----------

## 1、指令格式
>一条asn指令由指令部分和参数部分组成。指令部分是必须存在的部分；不同指令具有不同个数的参数，但是指令至少0个，至多三个，参数与参数间用逗号分隔.  

  
**asn指令格式：**`opcode [arg1],[arg2],[arg3]`
## 2、参数类型
>asn有三种参数类型，分别是：立即数、指针、寄存器


1、立即数是一个常数，不加任何修饰，如：`mov r0,89`，89就是一个立即数。  
2、指针是一个指向内存的地址，在立即数前加#表示这个数是一个指针，如：`mov r0,#100`,#100就是指向内存地址为100的指针。  
3、寄存器是虚拟机内定义的所有寄存器，目前总共有15个寄存器，各寄存器如下表所示：  
**注意：**事实上由于指令判断的方式，立即数和指针在大多时候都可以混用。
<table cellspacing="0">
    <tr>
        <th>寄存器</th>
        <th>功能</th>
    </tr>
    <tr>
        <td>R0</td>
        <td rowspan='3'>通用寄存器</td>
    </tr>
    <tr>
        <td><b>&middot;&middot;&middot;</b></td>
    </tr>
    <tr>
        <td>R9</td>
    </tr>
    <tr>
        <td>PC或R10</td>
        <td>程序计数器</td>
    </tr>
    <tr>
        <td>lr或R11</td>
        <td>连接寄存器</td>
    </tr>
    <tr>
        <td>sp或R12</td>
        <td>栈寄存器</td>
    </tr>
    <tr>
        <td>dptr或R13</td>
        <td>指针寄存器<br>(已经废除，可以作为通用寄存器使用,<br>在program-n中作为临时变量堆栈指针使用)</td>
    </tr>
    <tr>
        <td>cpsr或R14</td>
        <td>状态寄存器</td>
    </tr>
</table>
## 3、指令集 ##
>asn目前包括22个指令，基本上能够满足简单的需求，后续会根据需求添加指令集


<table cellspacing="0">
    <tr>
        <th>序号</th>
        <th>指令</th>
        <th>使用方式</th>
    </tr>
	<tr>
        <td>1</td>
        <td>mov</td>
        <td>数据转移指令</td>
    </tr>
	<tr>
        <td>2</td>
        <td>str</td>
        <td>数据存储指令</td>
    </tr>
	<tr>
        <td>3</td>
        <td>ldr</td>
        <td>数据加载指令</td>
    </tr>
	<tr>
        <td>4</td>
        <td>push</td>
        <td>数据入栈指令</td>
    </tr>
	<tr>
        <td>5</td>
        <td>pop</td>
        <td>数据出栈指令</td>
    </tr>
	<tr>
        <td>6</td>
        <td>jmp</td>
        <td>无条件跳转指令</td>
    </tr>
	<tr>
        <td>7</td>
        <td>cjmp</td>
        <td>条件跳转指令</td>
    </tr>
	<tr>
        <td>8</td>
        <td>bjmp</td>
        <td>带返回跳转指令</td>
    </tr>
	<tr>
        <td>9</td>
        <td>ret</td>
        <td>返回指令</td>
    </tr>
	<tr>
        <td>10</td>
        <td>end</td>
        <td>程序结束指令</td>
    </tr>
	<tr>
        <td>11</td>
        <td>add</td>
        <td>加法指令</td>
    </tr>
	<tr>
        <td>12</td>
        <td>sub</td>
        <td>减法指令</td>
    </tr>
	<tr>
        <td>13</td>
        <td>mul</td>
        <td>乘法指令</td>
    </tr>
	<tr>
        <td>14</td>
        <td>gt</td>
        <td>大于判断指令</td>
    </tr>
	<tr>
        <td>15</td>
        <td>gte</td>
        <td>大于等于判断指令</td>
    </tr>
	<tr>
        <td>16</td>
        <td>lt</td>
        <td>小于判断指令</td>
    </tr>
	<tr>
        <td>17</td>
        <td>lte</td>
        <td>小于等于判断指令</td>
    </tr>
	<tr>
        <td>18</td>
        <td>entry</td>
        <td>加载动态库指令</td>
    </tr>
	<tr>
        <td>19</td>
        <td>call</td>
        <td>调用动态库指令</td>
    </tr>
	<tr>
        <td>20</td>
        <td>exit</td>
        <td>卸载动态库指令</td>
    </tr>
	<tr>
        <td>21</td>
        <td>strb</td>
        <td>字节存储指令</td>
    </tr>
	<tr>
        <td>22</td>
        <td>strb</td>
        <td>字节加载指令</td>
    </tr>
</table>
## 4、使用指令
>首先约定：rn表示任意寄存器，#ptr表示指针，data表示立即数，sectionFlag是段标志。


### (1) mov指令
	mov rn,[rn,#ptr,data]
	将参数二表示的数据写入参数一。
	参数一必须是寄存器，参数二可以为任意类型数据。
### (2) str指令
	str rn,[rn,#ptr,data]
	将参数一中的数据写入到参数二指向的内存中。
	参数一必须是寄存器，参数二可以为任意类型数据。
### (3) ldr指令
	ldr rn,[rn,#ptr,data]
	将参数二指向的内存空间中的数据加载到参数一中。
	参数一必须是寄存器，参数二可以为任意类型数据。
### (4) push指令
	push rn
	将参数一压入到栈顶。
	参数一必须是寄存器。
### (5) pop指令
	pop rn
	将栈顶数据出栈到参数一中。
	参数一必须是寄存器。
### (6) jmp指令
	jmp sectionFlag
	无条件跳转到参数一指向的段。
	参数一是段标志。
### (7) cjmp指令
	cjmp sectionFlag
	首先判断cpsr的溢出标志，如果溢出则跳转到参数一指向的段。
	参数一是段标志。
### (8) bjmp指令
	bjmp sectionFlag
	带返回的跳转指令，与ret配合使用。
	参数一是段标志。
### (9) ret指令
	ret
	返回到链接寄存器指向的指令，与bjmp配合实现函数功能。
### (10) end指令
	end
	程序结束指令，运行到此处程序退出。
### (11) add指令
	add rn,rn,rn
	将参数二与参数三相加，结果存储到参数一中。
	三个参数都必须是寄存器。
### (12) sub指令
	sub rn,rn,rn
	将参数二与参数三相减，结果存储到参数一中。
	三个参数都必须是寄存器。
### (13) mul指令
	mul rn,rn,rn
	将参数二与参数三相乘，结果存储到参数一中。
	三个参数都必须是寄存器。
### (14) gt指令
	gt rn,rn
	判断参数一是否大于参数二，如果大于，将cpsr溢出标志置位。
	两个参数都必须是寄存器。
### (15) gte指令
	gte rn,rn
	判断参数一是否大于等于参数二，如果大于等于，将cpsr溢出标志置位。
	两个参数都必须是寄存器。
### (16) lt指令
	lt rn,rn
	判断参数一是否小于参数二，如果小于，将cpsr溢出标志置位。
	两个参数都必须是寄存器。
### (17) lte指令
	lte rn,rn
	判断参数一是否小于等于参数二，如果小于等于，将cpsr溢出标志置位。
	两个参数都必须是寄存器。
### (18) entry指令
	entry rn
	加载动态链接库，参数一是一个地址，地址指向到内存中动态库完全路径的字符串。
	参数一必须是寄存器。
### (19) call指令
	call rn
	调用动态链接库中的函数，参数一是一个地址，地址指向到内存中函数名的字符串。
	参数一必须是寄存器。
### (20) exit指令
	exit
	释放动态链接库
### (21) strb指令
	strb rn,[rn,#dptr],[rn,data]
	将参数一最低一个字节的数据存储到参数二指向的内存中的第参数三个位置。
	参数一必须是寄存器，参数二是寄存器或指针，参数三是立即数或寄存器。
### (22) ldrb指令
	ldrb rn,[rn,#dptr],[rn,data]
	将数据存储到参数二指向的内存中的第参数三个位置的一个字节数据加载到参数一中。
	参数一必须是寄存器，参数二是寄存器或指针，参数三是立即数或寄存器。
**注意：**从上面的详细信息可以看出只有在strb和ldrb中指针和立即数才存在区别。  
## 5、模块与段 ##
>为了增强asn的模块化能力，asn提供了段和模块来实现模块化。

### （1） 段 ###
>段是asn中最基本的模块化工具，利用段和三种跳转指令可以实现选择结构、循环结构和函数。 

 
**选择结构：**


	section yes:
		;真分支
		end
	lt r0,r1
	cjmp yes
	;假分支
	end
**循环结构：**

	section loop:
		;循环过程
		mov r1,10
		mov r2,1
		add r0,r0,r2
		lt r0,r1
		cjmp loop
		end
**函数：**	

	section testfunc:
		;函数过程
		ret
	bjmp testfunc
	end
### （2） 模块 ###
>模块是一个独立的asn源文件，模块中最基本的单位是函数，如果在模块中写入非函数代码，这些代码将不可用。一个模块有一个或多个函数组成。利用import指令可以将模块加载到当前模块中。


**模块引用：**


import后的参数是模块相对于当前模块的相对路径，将路径分隔符（'/'或'\'）替换为‘.’，将后缀省略。


	import lib.io
事实上由于模块是直接加载到当前文件的，一般在模块引用之前将程序跳转到入口函数中，如：
	

	jmp main
	import lib.io
	section main:
		;主程序
		end
**注意：**模块不能重复引用，在一个地方引用后，在程序中所有地方都能使用。

## 6、注释 ##
>目前只支持单行注释，使用逗号作为注释的开始,如：


	;注释

## 7、运行模式 ##
>asn提供了四种运行模式用于控制虚拟机在不同状态下可以运行的指令，四种模式分别是：用户模式、管理模式、系统模式、中断模式。

<table cellspacing="0">
    <tr>
        <th>代码</th>
        <th>模式</th>
        <th>介绍</th>
    </tr>
	<tr>
		<td>USR</td>
		<td>用户模式</td>
		<td>用户模式是权限最低的模式，具有寄存器操作、内存操作、运算符等指令权限</td>
	</tr>
	<tr>
		<td>SVC</td>
		<td>管理模式</td>
		<td>管理模式是进入系统模式的唯一途径，管理模式中可以切换到除中断模式外的其他模式</td>
	</tr>
	<tr>
		<td>SYS</td>
		<td>系统模式</td>
		<td>系统模式是asn中唯一一种可以访问到外部库的模式，只能通过管理模式进入到系统模式</td>
	</tr>
	<tr>
		<td>IRQ</td>
		<td>中断模式</td>
		<td>中断模式是系统发生中断异常时进入的模式，用户不能通过任何方式直接进入到中断模式，<br>
		只能通过配置中断寄存器并在满足条件时进入
		</td>
	</tr>
</table>


###cpsr寄存器

<table cellspacing="0">
    <tr>
        <th>位</th>
        <th>标志</th>
    </tr>
	<tr>
        <td>1</td>
        <td>0:正常状态<br>
		1:溢出状态
		</td>
    </tr>
	<tr>
        <td>2-3</td>
        <td>
			00:USR模式<br>
			01:SVC模式<br>
			10:SYS模式<br>
			11:IRQ模式<br>
		</td>
    </tr>
	<tr>
        <td>其他</td>
        <td>
			待定
		</td>
    </tr>
</table>

###异常偏移地址


	.0:jmp reset
	.1:jmp svc
	.2:jmp sys
	.3:jmp irq