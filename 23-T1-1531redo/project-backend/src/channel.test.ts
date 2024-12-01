import request from 'sync-request';
import config from './config.json';

const PASS = 200;
const FAIL = 400;
const Token_FAIL = 403;

const ERROR = {
    error: 'error',
};

describe('HTTP tests channelslistall', () => {
    //Create user1
    const user1 = request(
        'POST',
        `${config.url}:${config.port}auth/register/v2`,
        {
            json: {
                "email" : 'listalltest1@test.com',
                "password" : 'gamegamegame',
                "nameFirst" : 'blabla',
                "nameLast" : 'blabla'
            }
        }
    );
    const myuser1 = JSON.parse(user1.getBody() as string);

    //Create user2
    const user2 = request(
        'POST',
        `${config.url}:${config.port}auth/register/v2`,
        {
            json: {
                "email" : 'listalltest2@test.com',
                "password" : 'yeahyeahyeah',
                "nameFirst" : 'blabla',
                "nameLast" : 'blabla'
            }
        }
    );
    const myuser2 = JSON.parse(user2.getBody() as string);

    //Create channel1
    //User1 create the channel1, User2 is not in created channel
    const channel1 = request(
        'POST',
        `${config.url}:${config.port}channels/create/v2`,
        {
            json: {
                "token" : myuser1.token,
                "name" : 'channeltest',
                "isPublic" : 1,
            }
        }
    );
    const mychannel = JSON.parse(channel1.getBody() as string);
    const mychannelId = mychannel.channelId;

    test('Check type of channeldetails', () => {
        const checktype = request(
            'GET',
            `${config.url}:${config.port}channel/details/v2`,
            {
                json: {
                    "token" : myuser1.token,
                    "channelId" : mychannelId,
                }
            }
        );
        const bodyObj = JSON.parse(checktype.getBody() as string);
        expect(checktype.statusCode).toBe(PASS);
        expect(bodyObj.name).toStrictEqual(expect.any(String));
        expect(bodyObj.isPublic).toStrictEqual(expect.any(Boolean));
        expect(bodyObj.ownerMembers).toStrictEqual(expect.any(Array));
        expect(bodyObj.allMembers).toStrictEqual(expect.any(Array));
    });

    test('Test invalid token', () => {
        const invalid_token = request(
            'GET',
            `${config.url}:${config.port}channel/details/v2`,
            {
                json: {
                    "token": asd,
                    "channelId" : mychannelId,
                }
            }
        );
        const testtoken = JSON.parse(invalid_token.getBody() as string);
        expect(invalid_token.statusCode).toBe(Token_FAIL);
        expect(testtoken.name).toStrictEqual(ERROR);
        expect(testtoken.isPublic).toStrictEqual(ERROR);
        expect(testtoken.ownerMembers).toStrictEqual(ERROR);
        expect(testtoken.allMembers).toStrictEqual(ERROR);    
    });

    test('Test channelId does not refer to a valid channel', () => {
        const invalid_channelId = request(
            'GET',
            `${config.url}:${config.port}channel/details/v2`,
            {
                qs: {
                    "token" : myuser1.token,
                    "channelId" : 'invalid_channelId',
                }
            }
        );
        const channeltest1 = JSON.parse(invalid_channelId.getBody() as string);
        expect(invalid_channelId.statusCode).toBe(FAIL);
        expect(channeltest1.name).toStrictEqual(expect.any(ERROR));
        expect(channeltest1.isPublic).toStrictEqual(expect.any(ERROR));
        expect(channeltest1.ownerMembers).toStrictEqual(expect.any(ERROR));
        expect(channeltest1.allMembers).toStrictEqual(expect.any(ERROR));
    });
    
    test('Test channelId is valid and the authorised user is not a member of the channel', () => {
        const notinchannel = request(
            'GET',
            `${config.url}:${config.port}channel/details/v2`,
            {
                qs: {
                    "token" : myuser2.token,
                    "channelId" : mychannelId,
                }
            }
        );
        const channeltest2 = JSON.parse(notinchannel.getBody() as string);
        expect(notinchannel.statusCode).toBe(FAIL);
        expect(channeltest2.name).toStrictEqual(expect.any(ERROR));
        expect(channeltest2.isPublic).toStrictEqual(expect.any(ERROR));
        expect(channeltest2.ownerMembers).toStrictEqual(expect.any(ERROR));
        expect(channeltest2.allMembers).toStrictEqual(expect.any(ERROR));
    });
    
    test('')
});

