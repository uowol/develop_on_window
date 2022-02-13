from selenium import webdriver
from selenium.webdriver.common.keys import Keys # send_keys에 들어갈 Key 제공 - Keys.RETURN = '\ue006 = enter
from time import sleep

options = webdriver.ChromeOptions()
options.add_argument('window-size=1920,1080')

driver = webdriver.Chrome('chromedriver', options=options)
driver.implicitly_wait(5)

driver.get(url='https://www.burgerking.co.kr/#/home')

about_store = driver.find_element_by_xpath('//*[@id="app"]/div/div[1]/div/div/div[2]/ul/li[2]/button/span')
about_store.click()

search_store = driver.find_element_by_xpath('//*[@id="app"]/div/div[1]/div/div/div[2]/ul/li[2]/ul/li/a')
search_store.click()

btn_near_store = driver.find_element_by_xpath('//*[@id="app"]/div/div[3]/div[3]/div/div[1]/div[1]/div[2]/div[2]/button')
btn_near_store.click()

sleep(2)

num_of_stores = int(driver.find_element_by_xpath('//*[@id="app"]/div/div[3]/div[3]/div/div[1]/div[2]/div/p/em/span').text)
print(num_of_stores)
stores_name = driver.find_elements_by_xpath('//*[@id="app"]/div/div[3]/div[3]/div/div[1]/div[2]/ul/li[*]/div/p/strong')
stores_address = driver.find_elements_by_xpath('//*[@id="app"]/div/div[3]/div[3]/div/div[1]/div[2]/ul/li[*]/div/div/p[1]/span[1]')
stores_phone_number = driver.find_elements_by_xpath('//*[@id="app"]/div/div[3]/div[3]/div/div[1]/div[2]/ul/li[*]/div/div/p[2]/span')

for idx in range(num_of_stores):
    store_info = [stores_name[idx].text, stores_address[idx].text, stores_phone_number[idx].text]
    print(store_info)

sleep(3) 
driver.close()