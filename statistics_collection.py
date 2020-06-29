from selenium import webdriver

chromedriver = "chromedriver.exe"
driver = webdriver.Chrome(chromedriver)
driver.get("https://coronavirus-monitor.ru/coronavirus-v-rossii/")
driver.find_element_by_class_name('open-table').click()
corona = driver.find_elements_by_xpath("//div[@class='statistics-row']")
f = open('country_infection_rate.txt', 'w')
f.write(str(len(corona)) + '\n')
for i in corona:
    _temp = i.text.split('\n')[1:3]
    f.write(_temp[0].replace(' ', '_') + " " + _temp[1] + '\n')
driver.quit()
