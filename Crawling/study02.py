import selenium # selenium 라이브러리 불러오기
from selenium import webdriver
from selenium.webdriver.common.by import By # 셀렉터를 제공

from selenium.webdriver.support import expected_conditions as EC # 만약 element를 찾을 수 있었으면 True 아니면 False를 반환
from selenium.webdriver.support.ui import WebDriverWait # 

driver = webdriver.Chrome('chromedriver')
driver.get(url='https://www.google.com/')
try:
    element = WebDriverWait(driver, 5).until( # 드라이버에서 다음 메소드를 최대 5초간 시도함
        EC.presence_of_element_located((By.CLASS_NAME , 'gLFyf')) # 0.5초마다 gLFyf라는 클래스의 element가 존재하는지 유무를 체크
    )
finally:
    driver.quit() # driver.close()