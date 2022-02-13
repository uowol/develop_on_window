from selenium import webdriver
from selenium.webdriver.common.keys import Keys # send_keys에 들어갈 Key 제공 - Keys.RETURN = '\ue006 = enter
from time import sleep

options = webdriver.ChromeOptions()
# options.add_argument('window-size=1920,1080')

driver = webdriver.Chrome('chromedriver', options=options)
driver.implicitly_wait(5)

driver.get(url='https://www.google.com/')

search_box = driver.find_element_by_xpath('/html/body/div[1]/div[3]/form/div[1]/div[1]/div[1]/div/div[2]/input')

search_box.send_keys('greeksharifa.github.io')
search_box.send_keys(Keys.RETURN)

elements = driver.find_elements_by_xpath('//*[@id="rso"]/div[*]/div/div/div/a/h3')

for element in elements:
    print(element.text)
    print(element.text, file=open('gorio.txt', 'a', encoding='utf-8'))

sleep(3)
driver.close()
