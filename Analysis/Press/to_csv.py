import pandas as pd
import itertools
import numpy as np
import re

df = pd.read_excel('vogue_reach.xlsx')

fashion_week = ['LFW February 2017','LFW September 2017','LFW February 2018']

df_list = []
for week in fashion_week:
    day = [x for x in range(1, 20)]
    first = ['Baseline']
    first[1:] = day
    df_list.append(first)

df= df.ix[:,[0,2,3,4,5,6,7,8,9,10]]
df.insert(1,'Day',list(itertools.chain.from_iterable(df_list)))

# decimals = 9
# for x in range(2,11):
#     df.iloc[:,x] = df.iloc[:,x].apply(lambda x: round(x,decimals))

numpy_full = df.values
main = numpy_full[:,2:10].astype(np.double)
index = numpy_full[:,10].astype(np.double)
index = index * 0.01

numpy_mult = main * index[:,np.newaxis]
numpy_round_1 = np.around(numpy_mult,7)

# print(numpy_mult)
firsttwo = numpy_full[:,0:2]
final_numpy_1 = np.concatenate((firsttwo,numpy_round_1),axis=1)

# save (no gain)
columns = list(df.columns.values)
columns = columns[:-1]
df_1 = pd.DataFrame(data=final_numpy_1,columns=columns)
df_1['Day'] = df.Day.astype('str')

#print(df_1.isnull().sum(axis = 0))
# print(df_1[df_1.Day.str.contains("Baseline")])
df_1 = df_1[~df_1.Day.str.contains("Baseline")]
df_1.reset_index(drop=True,inplace=True)
df_1.to_csv('vogue_reach_mult.csv', encoding='utf-8', index=False)

# save (with gain)
fw1_ind = numpy_mult[0,:]
fw1_days = numpy_mult[1:20,:]
fw1 = fw1_days / fw1_ind

fw2_ind = numpy_mult[20,:]
fw2_days = numpy_mult[21:40,:]
fw2 = fw2_days / fw2_ind

fw3_ind = numpy_mult[40,:]
fw3_days = numpy_mult[41:60,:]
fw3 = fw3_days / fw3_ind

fw_full = np.concatenate(([fw1,fw2,fw3]),axis=0)
numpy_round_2 = np.around(fw_full,7)
firsttwo = numpy_full[:,0:2]
firsttwo = np.delete(firsttwo,[0,20,40],axis=0)
final_numpy_2 = np.concatenate((firsttwo, numpy_round_2),axis=1)

columns = [x + ' Daily Gain' for x in columns]
df_2 = pd.DataFrame(data=final_numpy_2,columns=columns)
df_2.to_csv('vogue_reach_mult_gain.csv', encoding='utf-8', index=False)

# print full df
df_2 = df_2.iloc[:,2:10]
df = pd.concat([df_1,df_2],axis=1)

fw1_match =  re.compile('LFW February 2017')
fw2_match =  re.compile('LFW September 2017')
fw3_match =  re.compile('LFW February 2018')

df['Fashion Week'] = df['Fashion Week'].str.replace(fw1_match, '1')
df['Fashion Week'] = df['Fashion Week'].str.replace(fw2_match, '2')
df['Fashion Week'] = df['Fashion Week'].str.replace(fw3_match, '3')

df.to_csv('vogue_reach_full.csv', encoding='utf-8', index=False)
print(df.shape)








