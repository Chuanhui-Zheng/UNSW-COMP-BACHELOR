import { authRegisterV1, authLoginV1 } from './auth';
import { channelDetailsV1, channelJoinV1, channelInviteV1} from './channel';
import { channelsCreateV1 } from './channels';
import { clearV1 } from './other';

const users = [
    {email: 'haydens@gmail.com', password: 'helloworld', nameFirst: 'Hayden', nameLast: 'Smith',},
    {email: 'timmy@gmail.com', password: 'password', nameFirst: 'Timmy', nameLast: 'White',},
    {email: 'jsnow@gmail.com', password: 'winter"s coming', nameFirst: 'Jone', nameLast: 'Snow',},
];
 
const ERROR = {
    error: 'error',
};

describe('Testing Global Owner Login', ()=>{
    let authUserId1, authUserId2,authUserId3;
    const is_public = false;

    test.each([
        {input_email: '130@qq.com', input_password: '123456',
        input_email2: '456@qq.com', input_password2: '-0987654',
        input_email3: 'aksj@163.com',input_password3: 'kjhgfd',},
        {input_email: 'ihugyt@okji.com', input_password: 'ijnhtfgvr',
        input_email2: 'poijsn@qq.com', input_password2: '0nn23983',
        input_email3: 'enjxh@163.com',input_password3: 'poiujhbs',},
        {input_email: 'oiuhgv@poi.com', input_password: '0987yhb',
        input_email2: 'knjbhyg@qq.com', input_password2: 'ihubhw2',
        input_email3: 'knbjhvs3@163.com',input_password3: 'jihgyvg',}
    ])('channelId refers to a channel that is private and the authorised user is not already a channel member and is not a global owner 1',
       ({input_email, input_password,input_email2,input_password2,input_email3,input_password3,}) =>{
        clearV1();
        authUserId1 = authRegisterV1(input_email, input_password, 'ijmknjbhnhgt', 'mkiuyhbn').authUserId;
        authUserId2 = authRegisterV1(input_email2, input_password2, 'ojihugyv', 'kojihugyvct').authUserId;
        authUserId3 = authRegisterV1(input_email3, input_password3, 'kojihugyf', 'kojihugy').authUserId;
        expect(authLoginV1(input_email2,  input_password2).authUserId).toStrictEqual(authUserId2);
        expect(authLoginV1(input_email, input_password).authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1(input_email3, input_password3).authUserId).toStrictEqual(authUserId3);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', is_public).channelId;
        let chanel2Id = channelsCreateV1(authUserId2, 'channel2', is_public).channelId;

        expect(channelJoinV1(authUserId1, chanel1Id)).toStrictEqual(ERROR);
        expect(channelJoinV1(authUserId2, chanel1Id)).toStrictEqual({});
        expect(channelJoinV1(authUserId3, chanel1Id)).toStrictEqual(ERROR);

        expect(channelJoinV1(authUserId1, chanel2Id)).toStrictEqual(ERROR);
        expect(channelJoinV1(authUserId2, chanel2Id)).toStrictEqual(ERROR);
        expect(channelJoinV1(authUserId3, chanel2Id)).toStrictEqual(ERROR);
    })
    
   

});