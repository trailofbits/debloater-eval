from ftplib import FTP
ftp = FTP()
ftp.connect("127.0.0.1", 8021)
ftp.login()


#1-9
ftp.pwd()
ftp.retrlines('LIST')
ftp.cwd('child')
ftp.retrlines('LIST')
ftp.cwd('..')
ftp.retrlines('LIST')
ftp.retrlines('RETR myfile.txt')
ftp.sendcmd('SITE CHMOD 444 myfile.txt')
ftp.mkd('deleteme')
ftp.rmd('deleteme')
ftp.rename('myfile.txt', 'myfile2.txt')
ftp.delete('myfile2.txt')
ftp.storbinary('STOR file')
ftp.quit()

