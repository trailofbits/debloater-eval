from ftplib import FTP
ftp = FTP()
ftp.connect("127.0.0.1", 8021)
ftp.login()

#10-14
ftp.delete('myfile.txt')
ftp.rmd('delete_me')
ftp.sendcmd('SITE CHMOD 444 myfile.txt')
ftp.storbinary('STOR file')
ftp.quit()

