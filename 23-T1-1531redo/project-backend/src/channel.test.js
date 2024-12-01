import { authRegisterV1, authLoginV1} from './auth';
import { channelDetailsV1, channelJoinV1, channelInviteV1} from './channel';
import { channelsCreateV1 } from './channels';
import { clearV1 } from './other';
import {userProfileV1} from './users.js'
const ERROR = {
    error: 'error',
};

describe('Test error case of channelDetailsV1',() =>{
    test.each([
        {input_email: '1301@qq.com', input_password: '1234590',
         input_first_name: 'Teacher', input_last_name: 'Hayden',
         input_email2: 'test1@test.com', channel_name: 'good_channel',},
         {input_email: '1xwnjk1@164.com', input_password: 'lkjhgfdsa',
         input_first_name: 'mklihbyutcrx', input_last_name: 'm;oibuvyctxrtdzr',
         input_email2: '0287654@test.com', channel_name: 'bad_channel',},
         {input_email: 'knwxelbui@swqijoh.com', input_password: '!@#$%%^*&^$%^*(@',
         input_first_name: 'oknjhsf6whs', input_last_name: 'isbuyfwwwx',
         input_email2: 'jiohg7t867@ogaytct.com', channel_name: 'whatTheHell',},
    ])('channelId does not refer to a valid channel.',
    ({input_email, input_password, input_first_name, input_last_name,input_email2,channel_name}) =>{
        clearV1();
        let password1= input_password;
        let password2= input_password+input_email+input_last_name;
        let authUserId1  = authRegisterV1(input_email, password1,input_first_name,input_last_name).authUserId;
        let authUserId2  = authRegisterV1(input_email2, password2, input_first_name+input_email2, input_email+input_password).authUserId;
        
        expect(authLoginV1(input_email, password1).authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1(input_email2, password2).authUserId).toStrictEqual(authUserId2);

        let channelId1 = channelsCreateV1(authUserId1, channel_name, true).channelId;
        let channelId2 = channelsCreateV1(authUserId2, channel_name+input_last_name, false).channelId;
        expect(channelDetailsV1(authUserId1, channelId1+channelId2+10205)).toStrictEqual(ERROR);
        expect(channelDetailsV1(authUserId2, channelId1*channelId2+100)).toStrictEqual(ERROR);
    })
});

describe('Test error case of channelDetailsV1',() =>{
    test.each([
        {input_email: '1301@qq.com', input_password: '1234590',
         input_first_name: 'Teacher', input_last_name: 'Hayden',
         input_email2: 'test1@test.com', channel_name: 'good_channel',},
         {input_email: '1xwnjk1@164.com', input_password: 'lkjhgfdsa',
         input_first_name: 'mklihbyutcrx', input_last_name: 'm;oibuvyctxrtdzr',
         input_email2: '0287654@test.com', channel_name: 'bad_channel',},
         {input_email: 'knwxelbui@swqijoh.com', input_password: '!@#$%%^*&^$%^*(@',
         input_first_name: 'oknjhsf6whs', input_last_name: 'isbuyfwwwx',
         input_email2: 'jiohg7t867@ogaytct.com', channel_name: 'whatTheHell',},
    ])('channelId is valid and the authorised user is not a member of the channel.',
    ({input_email, input_password, input_first_name, input_last_name,input_email2,channel_name}) =>{
        clearV1();
        let password1= input_password;
        let password2= input_password+input_email+input_last_name;

        let authUserId1  = authRegisterV1(input_email, input_password,input_first_name,input_last_name).authUserId;
        let authUserId2  = authRegisterV1(input_email2, input_password+input_email+input_last_name, input_first_name+input_email2, input_email+input_password).authUserId;

        expect(authLoginV1(input_email, password1).authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1(input_email2, password2).authUserId).toStrictEqual(authUserId2);

        let channelId1 = channelsCreateV1(authUserId1, channel_name, true).channelId;
        let channelId2 = channelsCreateV1(authUserId2, channel_name+input_last_name, false).channelId;
        expect(channelDetailsV1(authUserId2, channelId1)).toStrictEqual(ERROR);
        expect(channelDetailsV1(authUserId1, channelId2)).toStrictEqual(ERROR);
    })
});

describe('test for error join channel', () => {
    test('channelId does not refer to a valid channel 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        expect(channelJoinV1(authUserId1, chanel1Id + 100)).toStrictEqual(ERROR);
    })
    test('channelId does not refer to a valid channel 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        expect(channelJoinV1(authUserId1, chanel1Id + 1000)).toStrictEqual(ERROR);
    })
    test('the authorised user is already a member of the channel 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        expect(channelJoinV1(authUserId1, chanel1Id)).toStrictEqual(ERROR);
    })
    test('the authorised user is already a member of the channel 2', () => {
        clearV1();
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId2, 'channel1', true).channelId;
        expect(channelJoinV1(authUserId2, chanel1Id)).toStrictEqual(ERROR);
    })
    test('channelId refers to a channel that is private and the authorised user is not already a channel member and is not a global owner 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelJoinV1(authUserId2, chanel1Id)).toStrictEqual(ERROR);
    })
    test('channelId refers to a channel that is private and the authorised user is not already a channel member and is not a global owner 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId3 = authRegisterV1('789@qq.com', '12345678', 'cc', 'dd').authUserId;

        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('789@qq.com', '12345678').authUserId).toStrictEqual(authUserId3);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelJoinV1(authUserId3, chanel1Id)).toStrictEqual(ERROR);
    })
});

describe('test for correct join channel_A', () => {
    test('example 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', 1).channelId;
        expect(channelJoinV1(authUserId2, chanel1Id)).toStrictEqual({});
    })
    test('example 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;

        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);

        let chanel1Id = channelsCreateV1(authUserId2, 'channel1', 1).channelId;
        expect(channelJoinV1(authUserId1, chanel1Id)).toStrictEqual({});
    })
});


describe('test for error invite channel', () => {
    test('channelId does not refer to a valid channel 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        expect(channelInviteV1(authUserId1, chanel1Id + 100, authUserId2)).toStrictEqual(ERROR);
    })
    test('channelId does not refer to a valid channel 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelInviteV1(authUserId1, chanel1Id + 100976750, authUserId2)).toStrictEqual(ERROR);
    })
    test('uId does not refer to a valid user 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        expect(channelInviteV1(authUserId1, chanel1Id, authUserId2 * 11)).toStrictEqual(ERROR);
    })
    test('uId does not refer to a valid user 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelInviteV1(authUserId1, chanel1Id, authUserId2 + authUserId1 + 100)).toStrictEqual(ERROR);
    })
    test('uId refers to a user who is already a member of the channel 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        channelJoinV1(authUserId2, chanel1Id);
        expect(channelInviteV1(authUserId1, chanel1Id, authUserId2)).toStrictEqual(ERROR);
    })
    test('uId refers to a user who is already a member of the channel 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        channelJoinV1(authUserId2, chanel1Id);
        let t = channelInviteV1(authUserId2, chanel1Id, authUserId1);
        expect(t).toStrictEqual(ERROR);
    })
    test('channelId is valid and the authorised user is not a member of the channel 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        let authUserId3 = authRegisterV1('789@qq.com', '12345678', 'cc', 'dd').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        expect(authLoginV1('789@qq.com', '12345678').authUserId).toStrictEqual(authUserId3);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', true).channelId;
        expect(channelInviteV1(authUserId2 + authUserId1 + authUserId3 + 100, chanel1Id, authUserId3)).toStrictEqual(ERROR);
    })
    test('channelId is valid and the authorised user is not a member of the channel 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        let authUserId3 = authRegisterV1('789@qq.com', '12345678', 'cc', 'dd').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        expect(authLoginV1('789@qq.com', '12345678').authUserId).toStrictEqual(authUserId3);
        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelInviteV1(authUserId2*5201314, chanel1Id, authUserId2)).toStrictEqual(ERROR);
    })
});

describe('test for correct invite channel', () => {
    test('example 1', () => {
        clearV1();
        let authUserId1 = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('456@qq.com', '12345678', 'bb', 'cc').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('456@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelInviteV1(authUserId1, chanel1Id, authUserId2)).toStrictEqual({});
    })
    test('example 2', () => {
        clearV1();
        let authUserId1 = authRegisterV1('ncenejce@qq.com', '12345678', 'aa', 'bb').authUserId;
        let authUserId2 = authRegisterV1('sxjnnjcw@qq.com', '12345678', 'bb', 'cc').authUserId;
        let authUserId3 = authRegisterV1('cenjjk@qq.com', '12345678', 'cc', 'dd').authUserId;

        expect(authLoginV1('ncenejce@qq.com', '12345678').authUserId).toStrictEqual(authUserId1);
        expect(authLoginV1('sxjnnjcw@qq.com', '12345678').authUserId).toStrictEqual(authUserId2);
        expect(authLoginV1('cenjjk@qq.com', '12345678').authUserId).toStrictEqual(authUserId3);

        let chanel1Id = channelsCreateV1(authUserId1, 'channel1', false).channelId;
        expect(channelInviteV1(authUserId1, chanel1Id, authUserId3)).toStrictEqual({});
    })
});

describe('Combine test',() =>{
    test.each([
        {input_email: '1301@sijio.com', input_password: '1234590',
         input_first_name: 'Teacher', input_last_name: 'Hayden',
         input_email2: 'test1@test.com', 
         input_first_name2: 'Kjsbhhxwmki', input_last_name2: 'Jhgfdnxbvs',
         channel_name: 'channel_first_smdi', channel_name_2: 'channel_second'},
         {input_email: 'klmnuigy@nkjbvyu.com', input_password: 'muiyvtctx',
         input_first_name: 'pokjihugyftrx', input_last_name: 'mojihug',
         input_email2: 'opjihugy@test.com', 
         input_first_name2: 'mlniobuvytc', input_last_name2: 'joihiugyftr',
         channel_name: 'jiohugyuftydrte', channel_name_2: 'moihugyftdr'},

         {input_email: 'jnbhv@sijio.com', input_password: '09876543',
         input_first_name: 'lknkbuivyctrx', input_last_name: 'knjbhv',
         input_email2: 'klnjbhvycty@test.com', 
         input_first_name2: 'lm;knjbhvgcfx', input_last_name2: 'klnjbujvyctrx',
         channel_name: 'lmnlkbiuvyctrx', channel_name_2: ';ojiohugyftdr'},
    ])('Test channelJoinV1, channelDetailsV1',
    ({input_email, input_password, input_first_name, input_last_name,input_email2,input_first_name2,input_last_name2,channel_name,channel_name_2}) =>{
    clearV1();
        // register user
    let authUserId1  = authRegisterV1(input_email, input_password, input_first_name, input_last_name).authUserId;
    let authUserId2  = authRegisterV1(input_email2, input_password + input_last_name, input_first_name2, input_last_name2).authUserId;

    expect(authLoginV1(input_email, input_password).authUserId).toStrictEqual(authUserId1);
    expect(authLoginV1(input_email2, input_password + input_last_name).authUserId).toStrictEqual(authUserId2);

    // create channel
    let channelId1 = channelsCreateV1(authUserId1, channel_name, false).channelId;
    let channelId2 = channelsCreateV1(authUserId2, channel_name_2, true).channelId;

    // join channel
    let join_result = channelJoinV1(authUserId1, channelId2);
    //console.log(join_result);
    // get channel details
    let channeldt1 = channelDetailsV1(authUserId1, channelId1);
    let channeldt2 = channelDetailsV1(authUserId2, channelId2);
    // check content of channel details
    // channel1
    expect(channeldt1.name).toStrictEqual(channel_name);

    expect(channeldt1.isPublic).toStrictEqual(false);
    expect(channeldt1.ownerMembers.length).toStrictEqual(1);
    let user_obj_1 = userProfileV1(authUserId1,authUserId1).user;
    let user_obj_2 = userProfileV1(authUserId2,authUserId2).user;

    // channel1
    expect(channeldt1.ownerMembers.length).toStrictEqual(1);
    expect(channeldt1.ownerMembers[0]).toStrictEqual(user_obj_1);
    expect(channeldt1.allMembers.length).toStrictEqual(1);
    expect(channeldt1.allMembers[0]).toStrictEqual(user_obj_1);
      
    // channel2
    expect(channeldt2.name).toStrictEqual(channel_name_2);
    expect(channeldt2.isPublic).toStrictEqual(true);
    expect(channeldt2.ownerMembers.length).toStrictEqual(1);
    expect(channeldt2.ownerMembers[0]).toStrictEqual(user_obj_2);
    expect(channeldt2.allMembers.length).toStrictEqual(2);
    expect(channeldt2.allMembers[0]).toStrictEqual(user_obj_2);
    expect(channeldt2.allMembers[1]).toStrictEqual(user_obj_1);

 })

 test.each([
    {input_email: '1301@sijio.com', input_password: '1234590',
     input_first_name: 'Teacher', input_last_name: 'Hayden',
     input_email2: 'test1@test.com', 
     input_first_name2: 'Kjsbhhxwmki', input_last_name2: 'Jhgfdnxbvs',
     channel_name: 'channel_first_smdi', channel_name_2: 'channel_second',
     input_email3: 'test3@test.com',},
     {input_email: 'nkljbvyftr@sijio.com', input_password: '09876r5e4',
     input_first_name: 'm;oihugyftd', input_last_name: ',;moinohugyftdr',
     input_email2: 'minubgyvftr@kijhuyg.com', 
     input_first_name2: 'kmlnjbujvyutc', input_last_name2: 'p[k09u8y7gf6tycfg',
     channel_name: 'okjihugyft', channel_name_2: 'kl njbhvgc',
     input_email3: 'jbhbvh@oijni.com',},
     {input_email: 'mihug@mlniub.com', input_password: 'omnibuvy',
     input_first_name: 'oph7gftcf vbj', input_last_name: 'mklhiugyftcf',
     input_email2: 'kojih8iugyv@test.com', 
     input_first_name2: 'p[koj8h7g6ftdr', input_last_name2: ',;omiugyft',
     channel_name: 'l;,mknibuigyftdr', channel_name_2: 'mlinubyvtcr',
     input_email3: 'mllknubyvt@lmklnjkbhjyvtc.com',},
])('Test channelInviteV1, channelDetailsV1',
({input_email, input_password, input_first_name, input_last_name,input_email2,input_first_name2,input_last_name2,channel_name,channel_name_2,input_email3}) =>{
    clearV1();
    // register user
let authUserId1  = authRegisterV1(input_email, input_password, input_first_name, input_last_name).authUserId;
let authUserId2  = authRegisterV1(input_email2, input_password + input_last_name, input_first_name2, input_last_name2).authUserId;
let authUserId3  = authRegisterV1(input_email3, input_password + input_last_name2, input_first_name2+input_last_name, input_last_name2+input_first_name).authUserId;

expect(authLoginV1(input_email, input_password).authUserId).toStrictEqual(authUserId1);
expect(authLoginV1(input_email2, input_password + input_last_name).authUserId).toStrictEqual(authUserId2);
expect(authLoginV1(input_email3, input_password + input_last_name2).authUserId).toStrictEqual(authUserId3);

// create channel
let channelId1 = channelsCreateV1(authUserId1, channel_name, false).channelId;
let channelId2 = channelsCreateV1(authUserId2, channel_name_2, true).channelId;

// join channel
let join_result = channelJoinV1(authUserId1, channelId2);
expect(join_result).toStrictEqual({});
let join_result_2 = channelJoinV1(authUserId3, channelId2);
expect(join_result_2).toStrictEqual({});
let invite_result_1 = channelInviteV1(authUserId1, channelId1, authUserId3);
expect(invite_result_1).toStrictEqual({});
let invite_result_2 = channelInviteV1(authUserId3, channelId1, authUserId2);
expect(invite_result_2).toStrictEqual({});

// get channel details
let channeldt1 = channelDetailsV1(authUserId1, channelId1);
let channeldt2 = channelDetailsV1(authUserId2, channelId2);
// check content of channel details
// channel1
expect(channeldt1.name).toStrictEqual(channel_name);

expect(channeldt1.isPublic).toStrictEqual(false);
expect(channeldt1.ownerMembers.length).toStrictEqual(1);
let user_obj_1 = userProfileV1(authUserId1,authUserId1).user;
let user_obj_2 = userProfileV1(authUserId2,authUserId2).user;
let user_obj_3 = userProfileV1(authUserId3,authUserId3).user;

// channel1
expect(channeldt1.ownerMembers.length).toStrictEqual(1);
expect(channeldt1.ownerMembers[0]).toStrictEqual(user_obj_1);
expect(channeldt1.allMembers.length).toStrictEqual(3);
expect(channeldt1.allMembers[0]).toStrictEqual(user_obj_1);
expect(channeldt1.allMembers[1]).toStrictEqual(user_obj_3);
expect(channeldt1.allMembers[2]).toStrictEqual(user_obj_2);
  
// channel2
expect(channeldt2.name).toStrictEqual(channel_name_2);
expect(channeldt2.isPublic).toStrictEqual(true);
expect(channeldt2.ownerMembers.length).toStrictEqual(1);
expect(channeldt2.allMembers.length).toStrictEqual(3);
expect(channeldt2.allMembers[0]).toStrictEqual(user_obj_2);
expect(channeldt2.allMembers[1]).toStrictEqual(user_obj_1);
expect(channeldt2.allMembers[2]).toStrictEqual(user_obj_3);

})

});
