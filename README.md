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
1. `gitclone https://github.com/CrystalGrape/assembly-n`
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