import os, json
import re
import pandas as pd
import datetime

def filenames(directory):
    """ This funtion returns a list of all files names in a directory
    dictionary_path - directory name
    outputs:
    content - list of filenames (e.g. luxury_impressions.csv and luxury_mentions.csv)
    """
    # onlyfiles = [f for f in listdir(directory+'/') if isfile(join(directory+'/', f))]

    list_filenames = []
    for root, dirs, files in os.walk(directory):
        for name in files:
            list_filenames.append(name)

    return list_filenames

def changeDate(date):
    date = datetime.datetime.strptime(date, '%d-%m-%Y')
    start_1 = datetime.datetime.strptime('10-02-2017','%d-%m-%Y')
    end_1 = datetime.datetime.strptime('28-02-2017','%d-%m-%Y')
    start_2 = datetime.datetime.strptime('08-09-2017','%d-%m-%Y')
    end_2 = datetime.datetime.strptime('26-09-2017','%d-%m-%Y')
    start_3 = datetime.datetime.strptime('09-02-2018','%d-%m-%Y')
    end_3 = datetime.datetime.strptime('27-02-2018','%d-%m-%Y')

    if start_1 <= date <= end_1:
        fashionweek = '1'

    if start_2 <= date <= end_2:
        fashionweek = '2'

    if start_3 <= date <= end_3:
        fashionweek = '3'

    return(fashionweek)

def main():
    # data_directory = 'data'

    fashionweeks = ['fw1','fw2','fw3']

    topics = ['sustainability', 'luxury', 'streetwear', 'british',
              'creativity', 'global', 'diversity', 'innovation',
              'emergingtalent', 'heritage', 'modelhealth', 'personalisation']

    df_list = []
    regex_mentions = re.compile('[a-z]*_mentions.xlsx')
    regex_impressions = re.compile('[a-z]*_impressions.xlsx')

    for fw in fashionweeks:

        # load fashion week files
        fw_files = filenames(fw)
        print(fw_files)
        fw_files = ' '.join(fw_files)

        for topic in topics:
            regex_topic = re.compile('{}_\w+.xlsx'.format(topic))
            topic_match = re.findall(regex_topic,fw_files)
            topic_match = ' '.join(topic_match)

            # read mentions from excel file
            mentions_path = re.search(regex_mentions,topic_match).group(0)
            df_mentions = pd.read_excel(fw+'/'+mentions_path, skiprows=5)

            # read impressions from excel file
            impressions_path = re.search(regex_impressions,topic_match).group(0)
            df_impressions = pd.read_excel(fw+'/'+impressions_path, skiprows=5)

            # merge dataframes
            df_merged = pd.merge(df_mentions, df_impressions, on='Date')

            # add topic column
            df_merged['Topic'] = topic
            df_merged['Topic'] = df_merged['Topic'].str.title()

            # remain columns
            df_merged.rename(columns={"actual impressions": "Impressions"}, inplace=True)

            # extract relevant columns
            df_merged = df_merged[['Date','Topic','Mentions','Impressions','Engagements']]

            # if fw == 'fw1':
            #     # drop first row
            #     df_merged = df_merged.iloc[1:]
            #     df_merged.reset_index(inplace=True)

            # if fw == 'fw2':
            #     #drop first three rows and last row
            #     df_merged = df_merged.iloc[3:]
            #     df_merged.reset_index(inplace=True)
            #     df_merged = df_merged[:-1]
            #     df_merged.reset_index(inplace=True)

            # fill NA
            df_merged.fillna({'Engagements':0},inplace=True)

            # convert engagements to int type
            df_merged.Engagements = df_merged.Engagements.astype(int)

            # create day column
            df_merged['Day'] = df_merged.index.values + 1

            df_list.append(df_merged)

    # concatenate
    df_main = pd.concat(df_list, ignore_index=True)

    # split datatime column
    df_main[['Date', 'Time']] = df_main.Date.str.split(expand=True)
    df_main.drop(['Time'], axis=1, inplace = True)

    # convert datetime to appropriate week (LFWW September 2017, LFWM January 2018, LFWW February 2018, LWFWM June 2018)
    df_main['Fashion Week'] = ''
    df_main['Fashion Week'] = df_main['Date'].map(changeDate)

    # rearrange dataframe
    df_main = df_main[['Fashion Week','Topic','Day','Mentions','Impressions','Engagements']]

    # drop rows where mentions, engagements, and impressions = 0
    # df_main = df_main[(df_main[['Mentions', 'Impressions','Engagements']] != 0).all(axis=1)]

    #df_main = df_main.sort_values(by=['Fashion Week','Day'])

    df_main.to_csv('pulsar_main.csv', encoding='utf-8', index=False)

if __name__ == '__main__':
    main()


