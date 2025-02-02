# Packet Sniffer Program 

This is a packet sniffer program written in C that uses **libpcap** to capture and analyze network traffic. 

It demonstrates Object-Oriented Programming **(OOP)** 
concepts in **C** applying **Incapsulation** ,**Inheritance** and **Polymorphism**  
while providing essential features like IP and transport layer protocol analysis (TCP, UDP, ICMP), as well as application layer protocol analysis (HTTP, HTTPS, and SSH).

Additionally, the program supports filtering packets by specific IP addresses or ports using command-line options and can save captured packets to a file for later analysis using tools like Wireshark.

## Features

- **Packet Capture**: Capture live network packets using libpcap.
- **IP Layer Parsing**: Display information from IP packets, including source/destination IP and other IP header fields.
- **TCP/UDP/ICMP Parsing**: Parse and display details of TCP, UDP, and ICMP packets.
- **Application Layer Protocols**: Analyze HTTP, HTTPS, and SSH packets and display relevant information.
- **Filtering**: Filter captured packets by specific source/destination IP addresses or ports.
- **Saving Packets**: Save captured packets to a file in pcap format, enabling you to open them with programs like Wireshark.

## Installation

```bash
sudo apt-get update
sudo apt-get install libpcap-dev gcc

```

 **Compiling the Code**
```
    gcc mysniffer.c packets.c -lpcap -o wirefish
```

**Run the program**
```
sudo ./wirefish <"filter"> -f <file.pcap>
```

examples:

```
sudo ./wirefish wlp4s0 "icmp or udp or tcp" -f wireFish.pcap      //to save capturing to 'wireFish.pcap' file
sudo ./wirefish wlp4s0 "tcp port 80"                //to filter on specific port

```

## Videos

[Showing how OOP concepts applied](https://drive.google.com/file/d/12TE5C4rhOuvJtllv2dT1LW7ztsplkcXp/view?usp=drive_link)


[run the program](https://drive.google.com/file/d/1ExdPXl3bfiUChh_XLFfmoTD9_wLIF86o/view?usp=sharing)













