### 不造重复的轮子

我是从大一下半学期的时候正式开始接触电子的。
在这之前我还是个刚入学的小萌新，傻里傻气啥都不懂的那种。我依旧记得我刚上大学第一个学期认真学习高数的时候，当时一门心思决定好好学习，每天想的都是怎么才能用更巧妙的方法解决那一道道导数算式，还建了个群专门来解答别人的遇到的高数问题。那个学期我最庆幸的就是认真学习了C语言，从基本的语法到后面的大型程序自己都思考过也动手做过，在不知不觉中迈过了通往程序世界的第一个门槛。
前面说自己下半学期正式开始接触电子，是因为自己上学期快结束的时候开始第一次知道单片机这个东西，知道了电子设计大赛，可以算是一个非正式的接触吧。假期我买了单片机的板子，收到货之后带着东西回了家，打算在家里闭门研究。然而就像我们的寒假作业从来没看过一样，我也一眼没看。到了假期快结束的时候，在家实在待的无聊，于是提前买了票早到了学校十天。大冬天，学校人少的可怜，我每天没人交流，也就安心学习单片机。这款单片机是STC89C51单片机，是最基础的单片机，芯片内部资源比较少，板子的外设却很多，但是对于入门来说绰绰有余了。我学习单片机的方式也很特别，买的时候人家送了光盘，里面有很多资料，我翻了一下只找到一些例程，于是决定自己慢慢研究这些代码。接下来就是反复试验，搞清楚每一行代码是做什么的，重复着写代码和下载看效果的过程。就这样每天宿舍亮灯开始起床写，到晚上熄灯睡觉每天感觉还是收获很大的，持续了四五天。在我一次找资料的时候我发现光盘里居然有别人录好的教学视频，心里一阵万马奔腾。果然，跟着视频进展颇快，到开学定时器和中断都已经学完，到此51的基本部分也就学的差不多了。
全国电子设计大赛是两年一届，单数年举办，所以可能偶数年入学的同学比较占便宜，可以参加两届，当然大一那次就是去划划水，收获一点比赛经验了。我大一参加的就是2015年的全国电赛，当时的队友是两个学长，做的是电源方向，我负责编程部分。暑假留校准备了很长时间，实验室还有两个大两届的学长，感谢他们没有学长的架子，着实交给我不少的东西，所以有好心的学长带入门比自己摸索强太多了。比赛的时候日夜不分，基本上每天的睡觉时间不超过6个小时，多睡一个小时都会觉得对不起队友。我当时只会单片机程序，硬件的部分几乎一窍不通，所以跟队友沟通起来也有困难。最后只把基础部分做出来了，拿了个省级二等奖。
到了大二，开始学习数模电，我听的特别认真，觉得这是自己的不足要赶快补起来。硬件基础知识有了后就课下接着在实验室做电源的部分。期间记忆比较深的就是参加了蓝桥杯的电子比赛，由于我一直在用STC15的单片机，所以比较熟悉，入门很快，当年也是我们学校唯一一个大二的学生获得国家二等奖的。当时自己还参加过飞思卡尔智能车，机器人等比赛，但是精力有限没有做的那么成功，但是却结识了一位硬件的高手也是后来的省电赛队友梁神。省电赛开始做的时候很痛苦，动不动就炸个电容烧个芯片，后来我们常常深夜探讨那些电路的解决方案，还好梁神和翔神人都比较老实，我们几乎没吵过架还过得乐滋滋的。我们一步步查资料，现在简单的板子上设计电路然后整个连接起来测试，最后居然用自制的逆变器带起来了几十瓦的灯泡，开心的不行。但是没过多久，在测试中电路又一次炸了，找了很长时间也没找到原因。直到测试前的一天我们还在通宵调试，在调试无果后，我备受打击，有很长一段时间都不能接受这个现实。

慢慢的我才明白了我其实意会错了比赛的真正的意义，在这个过程中我已经收获了很多友情和知识，比赛的结果也只是一部分而已。到了大三，自己开始有了新的打算，觉得自己的性格适合搞科研，所以开始投入一部分时间到比赛之外的领域去，心境也平和了许多。第三次参加电赛的时候，就像见老朋友一样，没有那么的紧张，四月份开始准备到八月份末比赛结束，三个人全心全意的投入其中，时间居然也过得飞快。
现在谈一下文章的题目——不造重复的轮子。我们这些人做比赛都是从零开始，有些人想想就退却了。但是有一个问题，我们每年一届一届的学生做过比赛，但是下一届又从零开始，有的人甚至不知道自己怎么入门和去往何处。所以我写这篇文章就是为了让一些想参加的同学找到我们踩过的脚印，然后接着走下去，这样也许他们能走的更远，不是吗？
这篇文章可能有些冗长，但是确实是我写着写着就这么多了，毕竟四年时光，笔下写的还算少的，回忆可能更加汹涌澎湃。我也还做过其他比赛，比如数学建模之类的，但是这里只谈最有心得的电赛。文章的最后附一些我对一些常见问题的见解，仅供参考。
1.学习和比赛怎么平衡
这个问题我纠结了四年，答案是专心学习和边学习边参加比赛都比较合适，学习方面我们院的崔神就是榜样，边学习边比赛也当然可以，我们院的崔神和我各实践了一个方向，最后殊途同归吧。
2.为什么要做比赛
    比赛开阔人的眼界，锻炼你的动手能力，如果你想知道书本上那些知识怎么用就去做比赛吧。纸上得来终觉浅，绝知此事要躬行，就是这个意思吧。
3.什么比赛值得去做
 就我个人做过的比赛而言，蓝桥杯电子比赛，电赛省赛和电赛国赛比较值得去做，精力有限，不要贪多。
4.找什么样的队友
    志同道合的，做过比赛的都是兄弟。
5.上哪里找资料
淘宝，电路城以及一些博客。
6.基本的学习顺序
我个人的建议是51单片机，STC15单片机到STM32。51入门，15准备蓝
桥杯，32用来做电赛。
7.比赛花钱吗


总体来说不花钱，基本上我比赛花的钱都以奖学金的方式回来了，还有知识无价。

最后附上我的邮件联系方式：sunyanqinyin@aliyun.com，我比较喜欢清静，所以其他联系方式一般不回，望周知。部分我准备比赛的STC15代码放在了Github上，需要自取：https://github.com/YiZhiXiaoGuLI/STC15
                            
​                                              
作者：孙焱
成笔于2018年4月8日晚
华中科技大学CPSS实验室 