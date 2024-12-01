import { authRegisterV1, authLoginV1 } from './auth';
import { channelsCreateV1, channelsListallV1, channelsListV1 } from './channels';
import { clearV1 } from './other';

const ERROR = {
    error: 'error',
};

test('Test succesfile channelsListallV1', () => {
    // clear data
    clearV1();
    // register user
    const email1 = 'test1@test.com';
    const email2 = 'test2@test.com';
    const password = 'testtesttest';
    const password2 = 'kojihuigy'; 
    let authUserId1  = authRegisterV1( email1, password,'1122','ksmlidnwoie').authUserId;
    let authUserId2  = authRegisterV1( email2, password2, 'slknkjw', 'test2').authUserId;
    expect(authLoginV1(email1, password).authUserId).toStrictEqual(authUserId1);
    expect(authLoginV1(email2, password2).authUserId).toStrictEqual(authUserId2);
    // create channel
    let is_public = true;
    let is_private = false;
    let channelId1 = channelsCreateV1(authUserId1, 'test1', is_public).channelId;
    let channelId2 = channelsCreateV1(authUserId2, 'test2', is_public).channelId;
    let channelId3 = channelsCreateV1(authUserId1, 'test3', is_private).channelId;
    // list channels
    let channel_return = channelsListallV1(authUserId1);
    expect(channel_return.channels.length).toStrictEqual(3);
    // check channelid and name
    expect(channel_return.channels[0].channelId).toStrictEqual(channelId1);
    expect(channel_return.channels[0].name).toStrictEqual('test1');
    expect(channel_return.channels[1].channelId).toStrictEqual(channelId2);
    expect(channel_return.channels[1].name).toStrictEqual('test2');
    expect(channel_return.channels[2].channelId).toStrictEqual(channelId3);
    expect(channel_return.channels[2].name).toStrictEqual('test3');
});

test('Test succesfile channelsListallV1', () => {
    clearV1();
    let authUserId1  = authRegisterV1('test1@test.com', 'testtesttest','test1','test1').authUserId;
    expect(authLoginV1('test1@test.com', 'testtesttest').authUserId).toStrictEqual(authUserId1);
    let channelId1 = channelsCreateV1(authUserId1, 'test1', true).channelId;
    let channel_return = channelsListallV1(authUserId1);
    expect(channel_return.channels.length).toStrictEqual(1);
});

//                                         //
/*        test channelsCreate              */
/*                                         */
describe('test for error channelsCreate', () => {
    let uId;
    beforeEach(()=>{
        clearV1();
        uId = authRegisterV1('123@qq.com', '12345678', 'a', 'b').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(uId);
    })
    test.each([
        { authUserId: 'abab', name: 'channel1', isPublic: 0 },
        { authUserId: 'abbb', name: 'channel2', isPublic: 1 },
        { authUserId: 'aaad', name: 'channel3', isPublic: 0 },
    ])('The id was not been found', ({ authUserId, name, isPublic }) => {
        expect(channelsCreateV1(authUserId+10, name, isPublic)).toStrictEqual(ERROR);
    })

    test.each([
        { authUserId: 'abab', name: '', isPublic: 0 },
        { authUserId: 'abbb', name: 'abcdefg132456798gbuokjldASZ', isPublic: 1 },
        { authUserId: 'aaad', name: 'eFRDAHBHCdvfshjidvgjnzdagf', isPublic: 0 },
    ])('The name of channel is not  satisfied', ({ authUserId, name, isPublic }) => {
        expect(channelsCreateV1(authUserId, name, isPublic)).toStrictEqual(ERROR);
    })
});

describe('test for correct 1 auth channelsCreate', () => {
    let u_id;
    beforeEach(() => {
        clearV1();
        u_id = authRegisterV1('123@qq.com', '12345678', 'aa', 'bb').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(u_id);
    })

    test('Test public channel', () => {
        expect(channelsCreateV1(u_id, 'channel1', true)).toStrictEqual(
            expect.objectContaining({
                channelId: expect.any(Number),
            })
        );
    })

    test('Test private channel', () => {
        expect(channelsCreateV1(u_id, 'channel1', false)).toStrictEqual(
            expect.objectContaining({
                channelId: expect.any(Number),
            })
        )
    });
});


describe('test for correct 1 more auths channelsCreate', () => {
    let u_id1, u_id2;
    beforeEach(() => {
        clearV1();
        u_id1 = authRegisterV1('123@qq.com', ';ojiohugyft', 'aa', 'bb').authUserId;
        u_id2 = authRegisterV1('133@qq.com', 'joiohugyftdr', 'ab', 'bb').authUserId;
        expect(authLoginV1('123@qq.com', ';ojiohugyft').authUserId).toStrictEqual(u_id1);
        expect(authLoginV1('133@qq.com', 'joiohugyftdr').authUserId).toStrictEqual(u_id2);
    })
    test('create1.test should pass', () => {
        expect(channelsCreateV1(u_id1, 'channel1', true)).toStrictEqual(
            expect.objectContaining({
                channelId: expect.any(Number),
            })
        )
        expect(channelsCreateV1(u_id2, 'channel2', false)).toStrictEqual(
            expect.objectContaining({
                channelId: expect.any(Number),
            })
        )
    });

    test('create2.test should pass', () => {
        expect(channelsCreateV1(u_id1, 'channel1', false)).toStrictEqual(
            expect.objectContaining({
                channelId: expect.any(Number),
            })
        )
        expect(channelsCreateV1(u_id2, 'channel2', false)).toStrictEqual(
            expect.objectContaining({
                channelId: expect.any(Number),
            })
        )
    });
});



////////////////////////////////////
/*          channelsListV1        */

describe('test for error channelsListV1', () => {
    let uId;
    beforeEach(()=>{
        clearV1();
        uId = authRegisterV1('123@qq.com', '12345678', 'a', 'b').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(uId);
    });
    test('The uid was not been found', () => {
        expect(channelsListV1(uId)).toStrictEqual(
            expect.objectContaining({
                channels:   [],
            })
        )
    });
});


describe('test for correct empty channelsListV1', () => {
    let uId, cId;
    beforeEach(()=>{
        clearV1();
        uId = authRegisterV1('123@qq.com', '12345678', 'a', 'b').authUserId;
        expect(authLoginV1('123@qq.com', '12345678').authUserId).toStrictEqual(uId);
        cId = channelsCreateV1(uId, 'Channel', true).channelId;
    });
    test('Empty channel List.test should pass', () => {
        let u_id_1 = authRegisterV1('123123@qq.com', '12345678', 'aww', 'dab').authUserId;
        expect(channelsListV1(u_id_1)).toStrictEqual(
            expect.objectContaining({
                channels : [],
            })
        )
    });

    test('1 channel List.test should pass', () => {
        expect(channelsListV1(uId)).toStrictEqual(
            expect.objectContaining({
                channels : [{
                    channelId:  expect.any(Number),
                    name:   'Channel',
                }],
            })
        )
    });

    test('multiple channels List.test should pass', () => {
        clearV1();
        let uId1 = authRegisterV1('1333123@qq.com', '12345678', 'dadad', 'bwewe').authUserId;
        channelsCreateV1(uId1, 'Channel1', 0).channelId;
        channelsCreateV1(uId1, 'Channel2', 0).channelId;
        channelsCreateV1(uId1, 'Channel3', 0).channelId;
        expect(channelsListV1(uId1)).toStrictEqual(
            expect.objectContaining({
                channels : [
                {
                    channelId:  expect.any(Number),
                    name:   'Channel1',
                },
                {
                    channelId:  expect.any(Number),
                    name:   'Channel2',
                },
                {
                    channelId:  expect.any(Number),
                    name:   'Channel3',
                }],
            })
        )
    });
});

