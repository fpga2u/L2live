## TEST L2live

### 数据

pcap文件 | 报文类型 | 源IP |组播目的IP|目的端口| 内容 |行情日期|行情消息总数
----------|-----|------|-------|---|---|------|---------|
ssz_20190311.pcapng  |UDP|192.168.11.111|224.60.33.83|8888| APEX 深圳L2行情|2019/03/11|665404
ssh_20211126f.pcap |UDP|192.168.11.111|224.60.33.83|8888| APEX 上海L2行情|2021/11/26|332708
sshBin_20211203.pcap|UDP|192.168.11.111|224.60.33.83|8888| APEX 上海L1行情(指数、股票)|2021/12/03| 10749
sshBin_20211203fund.pcap|UDP-Lite|192.168.11.111|224.60.33.83|8888| APEX 上海L1行情(基金)|2021/12/03| 1857
sshBin_20211203opt.pcap|UDP-Lite|192.168.11.111|224.60.33.83|8888| APEX 上海L1行情(期权)|2021/12/03| 11012

### 测试环境

* 数据发送PC 1台， Linux

* 数据接收PC 1台， Linux or Windows

* 确保发送和接收PC在同一网段，互相可ping通

### 使用方法

> 接收侧

1. 在接收PC上打开L2live-qt_L2Viewer(若系统为Lixun需用sudo)，设置监听IP和端口为数据内【组播目的IP】和【目的端口】，设置类型为数据【UDP/UDP-Lite类型】。

    * 注意：Windows仅支持接收UDP类型

2. 若接收PC为Linux，则选择需设置绑定网卡为与发送PC同网段的网卡；若为Windows，则可选择自动。

3. 点击开始，启动接收。

> 发送侧

1. 在发送PC上查看与接收PC同网段的网卡名称和IP，使用以下命令生成对应网段的测试数据：

```shell
# 以pcap文件ssz_20190311.pcapng、发送PC的网卡名为enp2s0f1、IP为10.9.3.195为例：
tcpprep -a server -i ssz_20190311.pcapng -o re.cach
tcprewrite --endpoints=224.60.33.83:10.9.3.195 -i ssz_20190311.pcapng -o ssz_20190311_re.pcapng -c re.cach
```

2. 使用以下命令发送测试数据：

```shell
 sudo tcpreplay -i enp2s0f1  ssz_20190311_re.pcapng
```
