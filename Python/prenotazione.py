from selenium import webdriver
import time
import os
import sys
import platform

password = input("Enter your Smart Edu password\n")

if platform.system() == 'Linux':
    browser = webdriver.Firefox(executable_path="./driver/geckodriver")
if platform.system() == 'Windows':
    browser = webdriver.Firefox(executable_path="./driver/geckodriver.exe")

browser.get('https://studenti.smartedu.unict.it/WorkFlow2011/Logon/Logon.aspx?ReturnUrl=%2fDefault.aspx%3fLogout.aspx&Logout.aspx' + sys.argv[1])

cf = '//*[@id="ctl01_contents_UserName"]'
pin = '//*[@id="ctl01_contents_UserPassword"]'