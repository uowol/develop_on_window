import selenium # selenium 라이브러리 불러오기
from selenium import webdriver
from selenium.webdriver import ActionChains

from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By # 셀렉터를 제공

from selenium.webdriver.support import expected_conditions as EC # 만약 element를 찾을 수 있었으면 True 아니면 False를 반환
from selenium.webdriver.support.ui import Select
from selenium.webdriver.support.ui import WebDriverWait # 

URL = 'https://www.burgerking.co.kr/#/store'

driver = webdriver.Chrome(executable_path='./chromedriver.exe') # 웹 드라이버 사용: 크롬 엔진
driver.get(url=URL)

driver.implicitly_wait(time_to_wait=5) # 암묵적으로 5초간 기다림
# time.sleep(5) # 명시적으로 5초간 기다림

driver.close()
