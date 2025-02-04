const getAvatarUrl = async (profileIdentifier) => {
    try {
        const response = await fetch(`https://api.gravatar.com/v3/profiles/${profileIdentifier}`, {
            method: 'GET',
            headers: {
                Authorization: process.env.GRAVATAR_API_KEY,
            },
        });
        const data = await response.json();
        const avatar_url = `${data.avatar_url}?s=200`;
        return avatar_url;
    } catch (error) {
        console.error('Error:', error);
    }
};

document.getElementById('gravatar-avatar').src = getAvatarUrl('lawrencegarciaaa');
