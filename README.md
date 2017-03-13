# assembly-n 使用向导 #
#简介：
>assembly-n是基于C++的虚拟机，在虚拟机上可以直接运行assembly-n汇编语言，未来assembly-n将作为program-n的中间语言。


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
        <td>指针寄存器<br>(已经废除，可以作为通用寄存器使用)</td>
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